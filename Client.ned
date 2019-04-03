//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 
// 
// TODO documentation
//
module Client
{
    parameters:
        @display("bgb=706,561;i=old/bwcomp,red;is=n");
        string name;
    gates:
        inout publicInterface;
        inout quantumInterface;

    submodules:
        clientPublicInterface: ClientPublicInterface {
            @display("p=155.94,453.13");
        }
        clientQuantumInterface: ClientQuantumInterface {
            @display("p=518.67,453.13");
        }
        
    connections:
        clientPublicInterface.externalCommunication <--> publicInterface;
        clientQuantumInterface.quantumChannelCommunication <--> quantumInterface;
}

