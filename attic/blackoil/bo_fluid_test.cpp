/*
  Copyright 2010 SINTEF ICT, Applied Mathematics.

  This file is part of the Open Porous Media project (OPM).

  OPM is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  OPM is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OPM.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "config.h"

#include <opm/porsol/blackoil/fluid/FluidMatrixInteractionBlackoil.hpp>
#include <opm/core/utility/parameters/ParameterGroup.hpp>
#include <dune/common/fvector.hh>

#include <iostream>

int main(int argc, char** argv)
try
{
    // Parameters.
    Opm::parameter::ParameterGroup param(argc, argv);

    // Parser.
    std::string ecl_file = param.get<std::string>("filename");
    Opm::EclipseGridParser parser(ecl_file);

    // Test the FluidMatrixInteractionBlackoil class.
    Opm::FluidMatrixInteractionBlackoilParams<double> fluid_params;
    fluid_params.init(parser);
    typedef Opm::FluidMatrixInteractionBlackoil<double> Law;
    Dune::FieldVector<double, 3> s, kr;
    const double temp = 300; // [K]
    int num = 41;
    for (int i = 0; i < num; ++i) {
        s[Law::Aqua] = 0.0;
        s[Law::Liquid] = double(i)/double(num - 1);
        s[Law::Vapour] = 1.0 - s[Law::Aqua] - s[Law::Liquid];
        Law::kr(kr, fluid_params, s, temp);
        std::cout.width(6);
        std::cout.fill(' ');
        std::cout << s[Law::Liquid] << "    " << kr << '\n';
    }

}
catch (const std::exception &e) {
    std::cerr << "Program threw an exception: " << e.what() << "\n";
    throw;
}

