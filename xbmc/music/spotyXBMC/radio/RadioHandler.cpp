/*
    spotyxbmc2 - A project to integrate Spotify into XBMC
    Copyright (C) 2011  David Erenger

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    For contact with the author:
    david.erenger@gmail.com
*/

#include "RadioHandler.h"
#include "../Settings.h"
#include "../XBMCUpdater.h"
#include "../Logger.h"

namespace addon_music_spotify {

RadioHandler::RadioHandler() {
  Logger::printOut("creating radio handler");
  //hardcode two radios, allow for any number of radios later maybe
  SxRadio *radio1 = new SxRadio(1, Settings::getRadio1From(), Settings::getRadio1To(), Settings::getRadio1Genres());
  SxRadio *radio2 = new SxRadio(2, Settings::getRadio2From(), Settings::getRadio2To(), Settings::getRadio2Genres());

  m_radios.push_back(radio1);
  m_radios.push_back(radio2);
  Logger::printOut("creating radio handler done");
}

RadioHandler* RadioHandler::m_instance = 0;
RadioHandler *RadioHandler::getInstance() {
  return m_instance ? m_instance : (m_instance = new RadioHandler);
}

void RadioHandler::deInit() {
  delete m_instance;
}

RadioHandler::~RadioHandler() {
  while (!m_radios.empty()) {
    delete m_radios.back();
    m_radios.pop_back();
  }
}

void RadioHandler::allTracksLoaded(int radioNumber) {
  XBMCUpdater::updateRadio(radioNumber);
}

vector<SxTrack*> RadioHandler::getTracks(int radioNumber) {
  Logger::printOut("get tracks handler");
  if (radioNumber - 1 < m_radios.size()) {
    //if (m_radios[radioNumber - 1]->isLoaded())
      return m_radios[radioNumber - 1]->m_tracks;
  }
  Logger::printOut("get tracks handler radio not loaded");
  vector<SxTrack*> empty;
  return empty;
}

int RadioHandler::getLowestTrackNumber(int radioNumber) {
  Logger::printOut("get lowest trackNumber handler");
  if (radioNumber - 1 < m_radios.size()) {
    return m_radios[radioNumber - 1]->m_currentPlayingPos;
  }
  return 0;
}

void RadioHandler::pushToTrack(int radioNumber, int trackNumber) {
  if (radioNumber - 1 < m_radios.size()) {
    m_radios[radioNumber - 1]->pushToTrack(trackNumber);
  }
}

} /* namespace addon_music_spotify */
