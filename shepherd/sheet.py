"""To Install: Run `pip install --upgrade google-api-python-client`"""

from __future__ import print_function

import os
import csv
from ydl import ydl_send

import httplib2  # pylint: disable=import-error
from googleapiclient import discovery  # pylint: disable=import-error,no-name-in-module
from oauth2client import client  # pylint: disable=import-error
from oauth2client import tools  # pylint: disable=import-error
from oauth2client.file import Storage  # pylint: disable=import-error

from utils import *

class Sheet:

    # If modifying these scopes, delete your previously saved credentials
    # at ~/.credentials/sheets.googleapis.com-python-quickstart.json
    SCOPES = 'https://www.googleapis.com/auth/spreadsheets'
    CLIENT_SECRET_FILE = 'sheets/client_secret.json'
    APPLICATION_NAME = 'Google Sheets API Python Quickstart'


    def get_credentials():
        """Gets valid user credentials from storage.

        If nothing has been stored, or if the stored credentials are invalid,
        the OAuth2 flow is completed to obtain the new credentials.

        Returns:
            Credentials, the obtained credential.
        """
        home_dir = os.path.expanduser('~')
        credential_dir = os.path.join(home_dir, '.credentials')
        if not os.path.exists(credential_dir):
            os.makedirs(credential_dir)
        credential_path = os.path.join(credential_dir,
                                    'sheets.googleapis.com-python-quickstart.json')

        store = Storage(credential_path)
        credentials = store.get()
        if not credentials or credentials.invalid:
            flow = client.flow_from_clientsecrets(CLIENT_SECRET_FILE, SCOPES)
            flow.user_agent = APPLICATION_NAME
            # Needed only for compatibility with Python 2.6
            credentials = tools.run_flow(flow, store)
            print('Storing credentials to ' + credential_path)
        return credentials


    def get_round(match_number):
        # return get_offline_match(match_number)
        info = None
        try:
            info =  get_online_round(match_number)
        except httplib2.ServerNotFoundError:
            info = get_offline_match(match_number)

        ydl_send(YDL_TARGETS.SHEPHERD, SHEPHERD_HEADER.SPREADSHEET_INFO, {
            "things": 4 #TODO: fill in
        })


    def write_scores(match_number, blue_score, gold_score):
        try:
            write_online_scores(match_number, blue_score, gold_score)
        except httplib2.ServerNotFoundError:
            print("Unable to write to spreadsheet")


    def get_online_round(match_number, round_number):
        """
        A lot of this is adapted from google quickstart.
        Takes the match number and returns a dictionary with the teams names
        and team numbers for that match.
        """
        credentials = get_credentials()
        http = credentials.authorize(httplib2.Http())
        discoveryUrl = ('https://sheets.googleapis.com/$discovery/rest?'
                        'version=v4')
        service = discovery.build('sheets', 'v4', http=http,
                                discoveryServiceUrl=discoveryUrl)
        spreadsheetId = CONSTANTS.SPREADSHEET_ID
        range_name = "Match Database!A2:Q"
        spreadsheet = service.spreadsheets()  # pylint: disable=no-member
        game_data = spreadsheet.values().get(
            spreadsheetId=spreadsheetId, range=range_name).execute()
        row = 0
        for i, j in enumerate(game_data['values']):
            print(f"j is {j}")
            if int(j[0]) == match_number:
                row = i
                break
        match = game_data['values'][row]

        return {
            "num": match[3 * round_number - 1],
            "name": match[3 * round_number]
        }



    def get_offline_match(match_number):
        """
        reads from the downloaded csv file in the event that the online file cannot
        be read from.
        """
        # TODO: this
        csv_file = open(CONSTANTS.CSV_FILE_NAME, newline='')
        match_reader = csv.reader(csv_file, delimiter=' ', quotechar='|')
        matches = list(match_reader)
        match = matches[match_number]
        match = " ".join(match)
        match = match.split(',')
        return {"b1name": match[3], "b1num": match[2],
                "b2name": match[5], "b2num": match[4],
                "g1name": match[7], "g1num": match[6],
                "g2name": match[9], "g2num": match[8]}

    # pylint: disable=too-many-locals


    def write_online_scores(match_number, blue_score, gold_score):
        """
        A method that writes the scores to the sheet
        """
        credentials = get_credentials()
        http = credentials.authorize(httplib2.Http())
        discoveryUrl = ('https://sheets.googleapis.com/$discovery/rest?'
                        'version=v4')
        service = discovery.build('sheets', 'v4', http=http,
                                discoveryServiceUrl=discoveryUrl)
        spreadsheetId = CONSTANTS.SPREADSHEET_ID

        range_name = "Match Database!A2:Q"
        spreadsheet = service.spreadsheets()  # pylint: disable=no-member
        game_data = spreadsheet.values().get(
            spreadsheetId=spreadsheetId, range=range_name).execute()
        row = 0
        for i, j in enumerate(game_data['values']):
            if not j:
                raise Exception("empty row in spreadsheet. plz be better.")
            if int(j[0]) == match_number:
                row = i
                break
        

        # TODO: get this working for reals

        range_name_1 = "'Match Database'!E" + str(row + 2)
        range_name_2 = "'Match Database'!H" + str(row + 2)

        score_sheets = service.spreadsheets()  # pylint: disable=no-member
        game_scores = score_sheets.values().get(
            spreadsheetId=spreadsheetId, range=range_name_1).execute()
        game_scores['values'] = [[blue_score]]
        game_scores = score_sheets.values().get(
            spreadsheetId=spreadsheetId, range=range_name_2).execute()
        game_scores['values'] = [[gold_score]]

        sheets = service.spreadsheets()  # pylint: disable=no-member
        sheets.values().update(spreadsheetId=spreadsheetId,
                            range=range_name, body=game_scores,
                            valueInputOption="RAW").execute()