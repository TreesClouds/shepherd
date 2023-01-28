# Equivalent to sheet.py but using local configuration

import yaml
from yaml.loader import SafeLoader
from ydl import ydl_send
from utils import YDL_TARGETS, SHEPHERD_HEADER, CONSTANTS

class Config:

    config_file = None
    config_data = None

    def __init__(self, config_file='config/config.yaml'):
        self.config_file = config_file
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
        ydl_send(*SHEPHERD_HEADER.SET_TEAMS_INFO(teams=teams))
