import yaml
from yaml.loader import SafeLoader

class ScoreBuilder:

    config_file = None
    objective_data = None

    def __init__(self, config_file):
        self.config_file = config_file

    def setup(self):
        with open('example.yaml') as f:
            self.objective_data = yaml.load(f, Loader=SafeLoader)
