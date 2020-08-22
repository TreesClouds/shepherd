import sys
import os
from Utils import *

def get_class_from_name(name):
    return globals()[name]

def get_attr_from_name(source, name):
    if not isinstance(source, type):
        raise Exception('{} is not a class.'.format(source))
    return getattr(source, name)

def parse_header(header):
    parts = header.split('.')
    if len(parts) != 2:
         raise Exception('{} is invalid.'.format(header))
    ex = None
    try:
        klass = get_class_from_name(parts[0])
    except KeyError:
        ex = Exception('{} is not recognized. Make sure this is a class of headers in Utils.py'.format(parts[0]))
    finally:
        if ex:
            raise ex
    ex = None
    try:
        name = get_attr_from_name(klass, parts[1])
    except AttributeError:
        ex = Exception('{} is not recognized. Make sure this is a header in {} in Utils.py'.format(parts[1], parts[0]))
    finally:
        if ex:
            raise ex
    return name

def execute_python(script):
    global LOCALVARS
    exec(script, LOCALVARS)

def evaluate_python(token):
    global LOCALVARS
    return  eval(token, LOCALVARS)

def tokenize_wait_exp(expression):
    original_expression = expression
    def helper_min(a, b):
        if a == -1 and b == -1:
            return None
        elif a == -1:
            return b
        elif b == -1:
            return a
        else:
            return min(a, b)
    tokens = expression.split('FROM')
    if len(tokens) != 2:
        raise Exception('expected to find FROM after <header> and before <target> in WAIT statement: WAIT {}'.format(original_expression))
    header = parse_header(remove_outer_spaces(tokens[0]))
    expression = tokens[1]
    if remove_outer_spaces(expression[0:helper_min(expression.find(' SET '),expression.find(' WITH '))].split('.')[0]) != 'LCM_TARGETS':
        raise Exception('was expecting a target in LCM_TARGETS for WAIT statement: WAIT {}'.format(original_expression))
    target = get_attr_from_name(LCM_TARGETS, remove_outer_spaces(expression[0:helper_min(expression.find(' SET '),expression.find(' WITH '))].split('.')[1]))
    expression = expression[helper_min(expression.find(' SET '),expression.find(' WITH ')):None]
    statements = {'SET' : [], 'WITH' : []}
    while 'SET ' in expression or 'WITH ' in expression:
        expression = remove_outer_spaces(expression)
        type = 'SET' if expression[0:4] == 'SET ' else 'WITH'
        if type == 'WITH' and expression[0:5] != 'WITH ':
            raise Exception('was expecting WITH or SET statement, or nothing after FROM in WAIT statement: WAIT {}'.format(original_expression))
        expression = expression[len(type):None]
        expression = remove_outer_spaces(expression)
        statements[type].append(remove_outer_spaces(expression[0:helper_min(expression.find(' SET '),expression.find(' WITH '))]))
        expression = expression[helper_min(expression.find(' SET '),expression.find(' WITH ')):None]
    return {'header' : header, 'target' : target, 'with_statements' : statements['WITH'], 'set_statements' : statements['SET']}


def wait_function(expression):
    original_expression = expression
    global CURRENT_HEADERS
    def helper_min(a, b):
        if a == -1 and b == -1:
            return None
        elif a == -1:
            return b
        elif b == -1:
            return a
        else:
            return min(a, b)
    CURRENT_HEADERS = []
    WAITING = True
    while ' AND ' in expression or ' OR ' in expression:
        expression = remove_outer_spaces(expression)
        found = helper_min(expression.find(' AND '),expression.find(' OR '))
        type = 'AND' if expression[found:found+5] == ' AND ' else 'OR'
        header = tokenize_wait_exp(expression[0:found])
        expression = expression[found + len(type) + 2:None]
        CURRENT_HEADERS.append({'header' : header, 'type' : type, 'received' : False})
    expression = remove_outer_spaces(expression)
    CURRENT_HEADERS.append({'header' : tokenize_wait_exp(expression), 'type' : type, 'received' : False})

def read_next_line():
    global LINE
    LINE += 1

def has_next_line():
    global LINE, FILE
    return LINE < len(FILE)

def line_at(line):
    global FILE
    return FILE[line]

def jump_to_line(line):
    global LINE
    LINE = line

def current_line():
    global LINE, FILE
    return FILE[LINE]

def process_line(line):
    global LINE
    if line[0] == ' ' :
        raise Exception('unexpected indent on line {}: {}'.format(LINE, line))
    found = False
    for key in COMMANDS.keys():
        if line[0:len(key)] == key:
            ex = None
            try:
                COMMANDS[key](remove_outer_spaces(line[len(key):None]))
            except Exception as exx:
                ex = Exception('an error occured on line {}:\n{}'.format(LINE, exx))
            finally:
                if ex:
                    raise ex
            found = True
            break
    if not found:
        raise Exception('unrecognized command on line {}:\n{}'.format(LINE, line))

def LCM_receive(header, dic={}):
    pass

def remove_outer_spaces(token):
    while len(token) > 0 and token[-1] == ' ':
        token = token[:-1]
    while len(token) > 0 and token[0] == ' ':
        token = token[1:]
    return token

def if_function(expression):
    global END_COUNT, LINE, END_COUNT_HEADS
    starting_count = END_COUNT
    starting_line = LINE
    END_COUNT_HEADS[LINE] = END_COUNT
    condition = evaluate_python(remove_outer_spaces(expression))
    END_COUNT += 1
    if not condition:
        while END_COUNT > starting_count:
            read_next_line()
            ex = None
            try:
                line = current_line()
            except Exception:
                ex = Exception("reached end of file while in the IF on line {}. You are probably missing an END".format(starting_line))
            finally:
                if ex:
                    raise ex
            if line[0] == ' ':
                raise Exception('unexpected indent on line {}: {}'.format(LINE, line))
            found = False
            for key in COMMANDS.keys():
                if line[0:len(key)] == key:
                    found = True
                    break
            if not found:
                raise Exception('unrecognized command on line {}:\n{}'.format(LINE, line))
            if line[0:2] == 'IF' :
                END_COUNT += 1
            if line[0:5] == 'WHILE' :
                END_COUNT += 1
            if line[0:3] == 'END' :
                END_COUNT -= 1

def end_function(expression):
    global END_COUNT, LINE, END_COUNT_HEADS
    END_COUNT -= 1
    end_count_heads = list(END_COUNT_HEADS.items())
    end_count_heads.sort()
    for item in end_count_heads[::-1]:
        if item[0] < LINE and item[1] == END_COUNT:
            if line_at(item[0])[0:5] == 'WHILE':
                jump_to_line(item[0]-1)
            break

def pass_function(expression):
    expression = remove_outer_spaces(expression)
    if evaluate_python(expression) or expression == '':
        print("TEST PASSED")
        sys.exit()

def fail_function(expression):
    expression = remove_outer_spaces(expression)
    if evaluate_python(expression) or expression == '':
        print("TEST FAILED")
        sys.exit()

def assert_function(expression):
    expression = remove_outer_spaces(expression)
    if expression == '':
        raise Exception('expected a python conditional expression after ASSERT')
    if evaluate_python(expression):
        print("TEST PASSED")
    else:
        print("TEST FAILED")
    sys.exit()

def emit_function(expression):

def with_function_wait(expression, data):
    parts = expression.split('=')
    if len(parts) != 2:
         raise Exception('WHEN statement: {} is invalid.'.format(expression))
    parts[0] = remove_outer_spaces(parts[0])
    parts[1] = remove_outer_spaces(parts[1])
    if parts[1][0] != "'" or parts[1][-1] != "'":
        raise Exception("expected second argument of WHEN statement: {} to be wrapped in '.".format(expression))
    ex = None
    try:
        global LOCALVARS
        LOCALVARS[parts[0]] = data[parts[1][1:-1]]
    except Exception:
        ex = Exception("malformed WHEN statement: {}".format(expression))
    finally:
        if ex:
            raise ex

def with_function_emit(expression, data):
    parts = expression.split('=')
    if len(parts) != 2:
         raise Exception('WHEN statement: {} is invalid.'.format(expression))
    #remove leading and trailing spaces around the '='
    while len(parts[0]) > 0 and parts[0][-1] == ' ':
        parts[0] = parts[0][:-1]
    while len(parts[1]) > 0 and parts[1][0] == ' ':
        parts[1] = parts[1][1:]
    if parts[0][0] != "'" or parts[0][-1] != "'":
        raise Exception("expected first argument of WHEN statement: {} to be wrapped in '.".format(expression))
    ex = None
    try:
        data[parts[0][1:-1]] = evaluate_python(parts[1])
    except valueError:
        ex = Exception("{} is undefined".format(parts[1]))
    except Exception:
        ex = Exception("malformed WHEN statement: {}".format(expression))
    finally:
        if ex:
            raise ex

def run_until_wait():
    global WAITING
    while has_next_line() and not WAITING:
        process_line(current_line())
        read_next_line()

def main():
    """
    reads the whole file in and places it in a python list on the heap.
    """
    global FILE
    if len(sys.argv) != 2:
        print('The tester takes a single argument, the name of a testing file')
        return
    script_dir = os.path.dirname(__file__)
    rel_path = "tests/{}".format(sys.argv[1])
    abs_file_path = os.path.join(script_dir, rel_path)
    file = open(abs_file_path, "r")
    for line in file:
        line = line[0:-1]
        FILE.append(line)
    file.close()

FILE = []
WAITING = False
LOCALVARS = {}
CURRENT_HEADERS = []
LINE = 0
END_COUNT = 0
END_COUNT_HEADS = {}
COMMANDS = {'WAIT' : wait_function,
            'RUN' : execute_python,
            'READ' : lambda line: print('READ is not implemented in this version, but its still good style to use it.'),
            'PRINT' : lambda line: print(line),
            'PRINTP' : lambda line: print(evaluate_python(line)),
            'IF' : if_function,
            'WHILE' : if_function,
            'END' : end_function,
            'PASS': pass_function,
            'FAIL': fail_function,
            'ASSERT': assert_function}

if __name__ == '__main__':
    main()
