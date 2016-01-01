import AppDispatcher from '../dispatcher/AppDispatcher';
import { ActionTypes } from '../constants/Constants';
import AnsibleClient from '../utils/AnsibleClient';
import _ from 'lodash';

var _timestamps = [0, 0, 0, 0];

var _needToUpdate = function(newGamepads) {
  _.forEach(newGamepads, function(gamepad, index) {
    if(gamepad && gamepad.timestamp > _timestampes[index]) {
      _timestamps[index] = gamepad.timestamp;
      return true;
    }
    return false;
  });
};

var _formatGamepadsForJSON = function(newGamepads) {
  let formattedGamepads = {};
  _.forEach(newGamepads, function(gamepad) {
    if (gamepad) {
      formattedGamepads[gamepad.index] = {
        index: gamepad.index,
        axes: gamepad.axes
      };
    }
  });
  return formattedGamepads;
};

// Private function that checks for updated Gamepad State
// Also sends data to griff by emitting to socket-bridge
var _updateGamepadState = function() {
  let newGamepads = navigator.getGamepads();
  if (_needToUpdate(newGamepads)) {
    AnsibleClient.sendMessage('gamepad', _formatGamepadsForJSON(newGamepads));
    GamepadActionCreators.updateGamepads(newGamepads);
  }
};

var GamepadActionCreators = {
  updateGamepads(gamepads) {
    AppDispatcher.dispatch({
      type: ActionTypes.UPDATE_GAMEPADS,
      gamepads: gamepads
    });
  },
  setUpdateInterval(delay) {
    // remove the previous interval, if present
    if(this._interval !== null) {
      clearInterval(this._interval);
      this._interval = null;
    }
    this._interval = setInterval(_updateGamepadState, delay);
  }
};

export default GamepadActionCreators;
