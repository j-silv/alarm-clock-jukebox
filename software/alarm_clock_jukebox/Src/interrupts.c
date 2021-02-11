/*

******PSEUDO-CODE*******

-------button ISR------:

switches = readSwitches();
button = readButtons();

switch(switches) {

  case CHANGE_ALARM :
    if (button == CHANGE_HOUR) {
      incrementAlarmHour();
    }
    else if (button == CHANGE_MINUTE) {
      incrementAlarmMinute();
    }
    break;

  case CHANGE_TIME :
    if (button == CHANGE_HOUR) {
      incrementTimeHour();
    }
    else if (button == CHANGE_MINUTE) {
      incrementTimeMinute();
    }
    break;

  case CHANGE_VOLUME :
    if (button == UP_BUTTON) {
      incrementVolume();
    }
    else if (button == DOWN_BUTTON) {
      decreaseVolume();
    }
    break;  

  // in this case, the user has multiple "modes" selected
  // indicate to user that this is the case (with flashing LED for ex.) or do nothing
  default :

}

*/