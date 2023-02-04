# Equivalent to sheet.py but using local configuration

import yaml
import json
from yaml.loader import SafeLoader
from ydl import YDLClient
from utils import YDL_TARGETS, SHEPHERD_HEADER, CONSTANTS

YC = YDLClient()

class Config:

    config_file = None
    config_data = None
    score_data = {}  # structure: {match_number: [blue_score, gold_score]}

    def __init__(self, config_file=CONSTANTS.CONFIG_FILE, score_backup=CONSTANTS.SCORES_FILE):
        self.config_file = config_file
        self.score_backup = score_backup
        with open(score_backup) as backup:
            data = json.load(backup)
            if not data:
                print(f"Score backup not found; new backup created from config.")
            else:
                self.score_data = json.load(backup)
                print(f"Score backup found; previous scores loaded.")
        self.update()

    def update(self):
        with open(self.config_file) as f:
            self.config_data = yaml.load(f, Loader=SafeLoader)

    def get_team(self, team_number):
        for team in self.config_data['teams']:
            if team['number'] == team_number:
                return team
        return {'school': 'Null Team', 'number': team_number}

    def get_match(self, match_number):
        teams = [{}, {}, {}, {}]
        numbers = self.config_data['matches'][match_number].split(",")
        assert len(numbers) == 4
        for i in range(4):
            team = self.get_team(int(i))
            teams[i]['team_num'] = team['number']
            teams[i]['team_name'] = team['school']
            try:
                teams[i]['team_ip'] = team['ip']
            except KeyError:
                teams[i]['team_ip'] = 'team{}.local'.format(team['number'])
        YC.send(*SHEPHERD_HEADER.SET_TEAMS_INFO(teams=teams))

    def read_scores(self, match_number):
        if match_number in self.score_data.keys():
            return self.score_data[match_number]
        return None, None

    def write_scores(self, match_number, blue_score, gold_score):
        self.score_data[match_number] = [blue_score, gold_score]
        with open(self.score_backup, "w") as out:
            json.dump(self.score_data, out)

    def send_scores_for_icons(self, match_number):
        # TODO: Rewrite send_scores_for_icons
        pass

    def write_match_info(self, match_number, teams):
        # TODO: Rewrite write_match_info
        pass

