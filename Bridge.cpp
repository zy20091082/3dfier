/*
  3dfier: takes 2D GIS datasets and "3dfies" to create 3D city models.
  
  Copyright (C) 2015-2016  3D geoinformation research group, TU Delft

  This file is part of 3dfier.

  3dfier is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  3dfier is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with 3difer.  If not, see <http://www.gnu.org/licenses/>.

  For any information or further details about the use of 3dfier, contact
  Hugo Ledoux 
  <h.ledoux@tudelft.nl>
  Faculty of Architecture & the Built Environment
  Delft University of Technology
  Julianalaan 134, Delft 2628BL, the Netherlands
*/


#include "Bridge.h"

float Bridge::_heightref = 0.8;

Bridge::Bridge(char *wkt, std::string pid, float heightref)
  : Flat(wkt, pid)
{
  _heightref = heightref;
}


bool Bridge::lift() {
  //lift_each_boundary_vertices(percentile);
  //smooth_boundary(5);
  lift_percentile(_heightref);
  return true;
}


bool Bridge::add_elevation_point(double x, double y, double z, float radius, LAS14Class lasclass, bool lastreturn) {
  if (lastreturn == true && lasclass != LAS_BUILDING && lasclass != LAS_WATER) {
    Flat::add_elevation_point(x, y, z, radius, lasclass, lastreturn);
  }
  return true;
}


TopoClass Bridge::get_class() {
  return BRIDGE;
}


bool Bridge::is_hard() {
  return true;
}


std::string Bridge::get_mtl() {
  return "usemtl Bridge\n";
}


std::string Bridge::get_citygml() {
  return "<EMPTY/>";
}


bool Bridge::get_shape(OGRLayer* layer) {
  return TopoFeature::get_shape_features(layer, "Bridge");
}