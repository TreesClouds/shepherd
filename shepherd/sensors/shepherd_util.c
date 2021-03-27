#include "shepherd_util.h"

// *************************** LOWCAR DEFINITIONS *************************** //

device_t DummyDevice = {
    .type = 0,
    .name = "DummyDevice",
    .num_params = 16,
    .params = {
        // Read-only
        {.name = "RUNTIME", .type = INT, .read = 1, .write = 0},
        {.name = "SHEPHERD", .type = FLOAT, .read = 1, .write = 0},
        {.name = "DAWN", .type = BOOL, .read = 1, .write = 0},
        {.name = "DEVOPS", .type = INT, .read = 1, .write = 0},
        {.name = "ATLAS", .type = FLOAT, .read = 1, .write = 0},
        {.name = "INFRA", .type = BOOL, .read = 1, .write = 0},
        // Write-only
        {.name = "SENS", .type = INT, .read = 0, .write = 1},
        {.name = "PDB", .type = FLOAT, .read = 0, .write = 1},
        {.name = "MECH", .type = BOOL, .read = 0, .write = 1},
        {.name = "CPR", .type = INT, .read = 0, .write = 1},
        {.name = "EDU", .type = FLOAT, .read = 0, .write = 1},
        {.name = "EXEC", .type = BOOL, .read = 0, .write = 1},
        // Read-able and write-able
        {.name = "PIEF", .type = INT, .read = 1, .write = 1},
        {.name = "FUNTIME", .type = FLOAT, .read = 1, .write = 1},
        {.name = "SHEEP", .type = BOOL, .read = 1, .write = 1},
        {.name = "DUSK", .type = INT, .read = 1, .write = 1},
    }};

device_t Arduino1 = {
    .type = 7,
    .name = "Arduino1",
    .num_params = 7,
    .params = {
        // Read-only
        {.name = "button1", .type = BOOL, .read = 1, .write = 0},
        {.name = "button2", .type = BOOL, .read = 1, .write = 0},
        {.name = "button3", .type = BOOL, .read = 1, .write = 0},
        {.name = "button4", .type = BOOL, .read = 1, .write = 0},
        {.name = "button5", .type = BOOL, .read = 1, .write = 0},
        {.name = "button6", .type = BOOL, .read = 1, .write = 0},
        {.name = "button7", .type = BOOL, .read = 1, .write = 0},
        // Read-able and write-able
        /*
        {.name = "PIEF", .type = INT, .read = 1, .write = 1},
        {.name = "FUNTIME", .type = FLOAT, .read = 1, .write = 1},
        {.name = "SHEEP", .type = BOOL, .read = 1, .write = 1},
        {.name = "DUSK", .type = INT, .read = 1, .write = 1},
        */
    }};

    device_t Arduino2 = {
    .type = 6,
    .name = "Arduino2",
    .num_params = 6,
    .params = {
        // Read-only
        {.name = "desert_linebreak", .type = BOOL, .read = 1, .write = 0},
        {.name = "dehydration_linebreak", .type = BOOL, .read = 1, .write = 0},
        {.name = "hypothermia_linebreak", .type = BOOL, .read = 1, .write = 0},
        {.name = "airport_linebreak", .type = BOOL, .read = 1, .write = 0},

        {.name = "fire_lever", .type = BOOL, .read = 1, .write = 0},

        {.name = "fire_light", .type = BOOL, .read = 0, .write = 1},
        // Read-able and write-able
        /*
        {.name = "PIEF", .type = INT, .read = 1, .write = 1},
        {.name = "FUNTIME", .type = FLOAT, .read = 1, .write = 1},
        {.name = "SHEEP", .type = BOOL, .read = 1, .write = 1},
        {.name = "DUSK", .type = INT, .read = 1, .write = 1},
        */
    }};

    device_t Arduino3 = {
    .type = 4,
    .name = "Arduino1",
    .num_params = 4,
    .params = {
        // Read-only
        {.name = "city_linebreak", .type = BOOL, .read = 1, .write = 0},
        {.name = "traffic_linebreak", .type = BOOL, .read = 1, .write = 0},

        {.name = "traffic_light", .type = BOOL, .read = 0, .write = 1},
        
        {.name = "traffic_button", .type = BOOL, .read = 1, .write = 0},
        // Read-able and write-able
        /*
        {.name = "PIEF", .type = INT, .read = 1, .write = 1},
        {.name = "FUNTIME", .type = FLOAT, .read = 1, .write = 1},
        {.name = "SHEEP", .type = BOOL, .read = 1, .write = 1},
        {.name = "DUSK", .type = INT, .read = 1, .write = 1},
        */
    }};


device_t LimitSwitch = {
    .type = 1,
    .name = "LimitSwitch",
    .num_params = 3,
    .params = {
        {.name = "switch0", .type = BOOL, .read = 1, .write = 0},
        {.name = "switch1", .type = BOOL, .read = 1, .write = 0},
        {.name = "switch2", .type = BOOL, .read = 1, .write = 0}}};

device_t LineFollower = {
    .type = 2,
    .name = "LineFollower",
    .num_params = 3,
    .params = {
        {.name = "left", .type = FLOAT, .read = 1, .write = 0},
        {.name = "center", .type = FLOAT, .read = 1, .write = 0},
        {.name = "right", .type = FLOAT, .read = 1, .write = 0}}};

device_t BatteryBuzzer = {
    .type = 3,
    .name = "BatteryBuzzer",
    .num_params = 8,
    .params = {
        {.name = "is_unsafe", .type = BOOL, .read = 1, .write = 0},
        {.name = "calibrated", .type = BOOL, .read = 1, .write = 0},
        {.name = "v_cell1", .type = FLOAT, .read = 1, .write = 0},
        {.name = "v_cell2", .type = FLOAT, .read = 1, .write = 0},
        {.name = "v_cell3", .type = FLOAT, .read = 1, .write = 0},
        {.name = "v_batt", .type = FLOAT, .read = 1, .write = 0},
        {.name = "dv_cell2", .type = FLOAT, .read = 1, .write = 0},
        {.name = "dv_cell3", .type = FLOAT, .read = 1, .write = 0}}};

device_t ServoControl = {
    .type = 4,
    .name = "ServoControl",
    .num_params = 2,
    .params = {
        {.name = "servo0", .type = FLOAT, .read = 1, .write = 1},
        {.name = "servo1", .type = FLOAT, .read = 1, .write = 1}}};

device_t PolarBear = {
    .type = 5,
    .name = "PolarBear",
    .num_params = 3,
    .params = {
        {.name = "duty_cycle", .type = FLOAT, .read = 1, .write = 1},
        {.name = "motor_current", .type = FLOAT, .read = 1, .write = 0},
        {.name = "deadband", .type = FLOAT, .read = 1, .write = 1}}};

device_t KoalaBear = {
    .type = 6,
    .name = "KoalaBear",
    .num_params = 16,
    .params = {
        {.name = "velocity_a", .type = FLOAT, .read = 1, .write = 1},
        {.name = "deadband_a", .type = FLOAT, .read = 1, .write = 1},
        {.name = "invert_a", .type = BOOL, .read = 1, .write = 1},
        {.name = "pid_enabled_a", .type = BOOL, .read = 1, .write = 1},
        {.name = "pid_kp_a", .type = FLOAT, .read = 1, .write = 1},
        {.name = "pid_ki_a", .type = FLOAT, .read = 1, .write = 1},
        {.name = "pid_kd_a", .type = FLOAT, .read = 1, .write = 1},
        {.name = "enc_a", .type = INT, .read = 1, .write = 1},
        // Same params as above except for motor b
        {.name = "velocity_b", .type = FLOAT, .read = 1, .write = 1},
        {.name = "deadband_b", .type = FLOAT, .read = 1, .write = 1},
        {.name = "invert_b", .type = BOOL, .read = 1, .write = 1},
        {.name = "pid_enabled_b", .type = BOOL, .read = 1, .write = 1},
        {.name = "pid_kp_b", .type = FLOAT, .read = 1, .write = 1},
        {.name = "pid_ki_b", .type = FLOAT, .read = 1, .write = 1},
        {.name = "pid_kd_b", .type = FLOAT, .read = 1, .write = 1},
        {.name = "enc_b", .type = INT, .read = 1, .write = 1},
    }};

// *********************** VIRTUAL DEVICE DEFINITIONS *********************** //

// A CustomDevice is unusual because the parameters are dynamic
// This is just here to avoid some errors when using get_device() on CustomDevice
// Used in niche situations (ex: UDP_TCP_CONVERTER_TEST)for Spring 2021 comp.
device_t CustomDevice = {
    .type = MAX_DEVICES,  // Also used this way in udp_conn.c
    .name = "CustomDevice",
    .num_params = 1,
    .params = {
        {.name = "time_ms", .type = INT, .read = 1, .write = 0}}};

device_t SoundDevice = {
    .type = 59,
    .name = "SoundDevice",
    .num_params = 2,
    .params = {
        {.name = "SOCK_FD", .type = INT, .read = 0, .write = 0},
        {.name = "PITCH", .type = FLOAT, .read = 1, .write = 1}}};

device_t TimeTestDevice = {
    .type = 60,
    .name = "TimeTestDevice",
    .num_params = 2,
    .params = {
        {.name = "GET_TIME", .type = BOOL, .read = 1, .write = 1},
        {.name = "TIMESTAMP", .type = INT, .read = 1, .write = 0}}};

device_t UnstableTestDevice = {
    .type = 61,
    .name = "UnstableTestDevice",
    .num_params = 1,
    .params = {
        {.name = "NUM_ACTIONS", .type = INT, .read = 1, .write = 0}}};

device_t SimpleTestDevice = {
    .type = 62,
    .name = "SimpleTestDevice",
    .num_params = 4,
    .params = {
        {.name = "INCREASING", .type = INT, .read = 1, .write = 0},
        {.name = "DOUBLING", .type = FLOAT, .read = 1, .write = 0},
        {.name = "FLIP_FLOP", .type = BOOL, .read = 1, .write = 0},
        {.name = "MY_INT", .type = INT, .read = 1, .write = 1},
    }};

device_t GeneralTestDevice = {
    .type = 63,
    .name = "GeneralTestDevice",
    .num_params = 32,
    .params = {
        // Read-only
        {.name = "INCREASING_ODD", .type = INT, .read = 1, .write = 0},
        {.name = "DECREASING_ODD", .type = INT, .read = 1, .write = 0},
        {.name = "INCREASING_EVEN", .type = INT, .read = 1, .write = 0},
        {.name = "DECREASING_EVEN", .type = INT, .read = 1, .write = 0},
        {.name = "INCREASING_FLIP", .type = INT, .read = 1, .write = 0},
        {.name = "ALWAYS_LEET", .type = INT, .read = 1, .write = 0},
        {.name = "DOUBLING", .type = FLOAT, .read = 1, .write = 0},
        {.name = "DOUBLING_NEG", .type = FLOAT, .read = 1, .write = 0},
        {.name = "HALFING", .type = FLOAT, .read = 1, .write = 0},
        {.name = "HALFING_NEG", .type = FLOAT, .read = 1, .write = 0},
        {.name = "EXP_ONE_PT_ONE", .type = FLOAT, .read = 1, .write = 0},
        {.name = "EXP_ONE_PT_TWO", .type = FLOAT, .read = 1, .write = 0},
        {.name = "ALWAYS_PI", .type = FLOAT, .read = 1, .write = 0},
        {.name = "FLIP_FLOP", .type = BOOL, .read = 1, .write = 0},
        {.name = "ALWAYS_TRUE", .type = BOOL, .read = 1, .write = 0},
        {.name = "ALWAYS_FALSE", .type = BOOL, .read = 1, .write = 0},
        // Read and Write
        {.name = "RED_INT", .type = INT, .read = 1, .write = 1},
        {.name = "ORANGE_INT", .type = INT, .read = 1, .write = 1},
        {.name = "GREEN_INT", .type = INT, .read = 1, .write = 1},
        {.name = "BLUE_INT", .type = INT, .read = 1, .write = 1},
        {.name = "PURPLE_INT", .type = INT, .read = 1, .write = 1},
        {.name = "RED_FLOAT", .type = FLOAT, .read = 1, .write = 1},
        {.name = "ORANGE_FLOAT", .type = FLOAT, .read = 1, .write = 1},
        {.name = "GREEN_FLOAT", .type = FLOAT, .read = 1, .write = 1},
        {.name = "BLUE_FLOAT", .type = FLOAT, .read = 1, .write = 1},
        {.name = "PURPLE_FLOAT", .type = FLOAT, .read = 1, .write = 1},
        {.name = "RED_BOOL", .type = BOOL, .read = 1, .write = 1},
        {.name = "ORANGE_BOOL", .type = BOOL, .read = 1, .write = 1},
        {.name = "GREEN_BOOL", .type = BOOL, .read = 1, .write = 1},
        {.name = "BLUE_BOOL", .type = BOOL, .read = 1, .write = 1},
        {.name = "PURPLE_BOOL", .type = BOOL, .read = 1, .write = 1},
        {.name = "YELLOW_BOOL", .type = BOOL, .read = 1, .write = 1}}};

// ************************ DEVICE UTILITY FUNCTIONS ************************ //

// An array that holds pointers to the structs of each lowcar device
device_t* DEVICES[DEVICES_LENGTH] = {0};
// A hack to initialize DEVICES. https://stackoverflow.com/a/6991475
__attribute__((constructor)) void devices_arr_init() {
    DEVICES[DummyDevice.type] = &DummyDevice;
    DEVICES[LimitSwitch.type] = &LimitSwitch;
    DEVICES[LineFollower.type] = &LineFollower;
    DEVICES[BatteryBuzzer.type] = &BatteryBuzzer;
    DEVICES[ServoControl.type] = &ServoControl;
    DEVICES[PolarBear.type] = &PolarBear;
    DEVICES[KoalaBear.type] = &KoalaBear;
    DEVICES[CustomDevice.type] = &CustomDevice;
    DEVICES[SoundDevice.type] = &SoundDevice;
    DEVICES[TimeTestDevice.type] = &TimeTestDevice;
    DEVICES[UnstableTestDevice.type] = &UnstableTestDevice;
    DEVICES[SimpleTestDevice.type] = &SimpleTestDevice;
    DEVICES[GeneralTestDevice.type] = &GeneralTestDevice;
    DEVICES[Arduino1.type] = &Arduino1;
}

device_t* get_device(uint8_t dev_type) {
    if (0 <= dev_type && dev_type < DEVICES_LENGTH) {
        return DEVICES[dev_type];
    }
    return NULL;
}

uint8_t device_name_to_type(char* dev_name) {
    for (int i = 0; i < DEVICES_LENGTH; i++) {
        if (DEVICES[i] != NULL && strcmp(DEVICES[i]->name, dev_name) == 0) {
            return i;
        }
    }
    return -1;
}

char* get_device_name(uint8_t dev_type) {
    device_t* device = get_device(dev_type);
    if (device == NULL) {
        return NULL;
    }
    return device->name;
}

param_desc_t* get_param_desc(uint8_t dev_type, char* param_name) {
    device_t* device = get_device(dev_type);
    if (device == NULL) {
        return NULL;
    }
    for (int i = 0; i < device->num_params; i++) {
        if (strcmp(param_name, device->params[i].name) == 0) {
            return &device->params[i];
        }
    }
    return NULL;
}

int8_t get_param_idx(uint8_t dev_type, char* param_name) {
    device_t* device = get_device(dev_type);
    if (device == NULL) {
        return -1;
    }
    for (int i = 0; i < device->num_params; i++) {
        if (strcmp(param_name, device->params[i].name) == 0) {
            return i;
        }
    }
    return -1;
}

// ********************************** TIME ********************************** //

/* Returns the number of milliseconds since the Unix Epoch */
uint64_t millis() {
    struct timeval time;  // Holds the current time in seconds + microseconds
    gettimeofday(&time, NULL);
    uint64_t s1 = (uint64_t)(time.tv_sec) * 1000;  // Convert seconds to milliseconds
    uint64_t s2 = (time.tv_usec / 1000);           // Convert microseconds to milliseconds
    return s1 + s2;
}

// ********************* READ/WRITE TO FILE DESCRIPTOR ********************** //

int readn(int fd, void* buf, uint16_t n) {
    uint16_t n_remain = n;
    uint16_t n_read;
    char* curr = buf;

    while (n_remain > 0) {
        if ((n_read = read(fd, curr, n_remain)) < 0) {
            if (errno == EINTR) {  // read interrupted by signal; read again
                n_read = 0;
            } else {
                perror("read");
                return -1;
            }
        } else if (n_read == 0) {  // received EOF
            return 0;
        }
        n_remain -= n_read;
        curr += n_read;
    }
    return (n - n_remain);
}

int writen(int fd, void* buf, uint16_t n) {
    uint16_t n_remain = n;
    uint16_t n_written;
    char* curr = buf;

    while (n_remain > 0) {
        if ((n_written = write(fd, curr, n_remain)) <= 0) {
            if (n_written < 0 && errno == EINTR) {  // write interrupted by signal, write again
                n_written = 0;
            } else {
                perror("write");
                return -1;
            }
        }
        n_remain -= n_written;
        curr += n_written;
    }
    return n;
}



/************** LOG_PRINTF STUB ***********/

void log_printf(int level, char* format, ...) {
    va_list args;
    va_start(args, format);
    
    int length = strlen(format) + 1;
    char buf[length + 1];
    strncpy(buf, format, length);
    if (buf[length-2] != '\n') {
        buf[length-1] = '\n';
        buf[length] = 0;
    }
    vprintf(buf, args);
    va_end(args);
}


