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

#ifndef THUMBSTORE_H_
#define THUMBSTORE_H_

#include <tr1/unordered_map>
#include <libspotify/api.h>

namespace addon_music_spotify {

class SxThumb;
class ThumbStore {
public:

  static ThumbStore *getInstance();
  static void deInit();


  SxThumb *getThumb(const byte* image);
  void removeThumb(const byte* image);
  void removeThumb(SxThumb* thumb);

private:
  ThumbStore();
  virtual ~ThumbStore();

  static ThumbStore *m_instance;

  typedef std::tr1::unordered_map<const byte*, SxThumb*> thumbMap;
  thumbMap m_thumbs;
};

} /* namespace addon_music_spotify */
#endif /* THUMBSTORE_H_ */
