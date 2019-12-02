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
network Network
{
    parameters:
        @figure[description](type=text; pos=90,-65; font=,,bold; text="[BB84 Protocol]"; color=green);
        @figure[details](type=text; pos=0,-40; text="Multipoint Quantum Key Distribution");

        @display("bgb=337,288,#FFE4CA;i=block/network;i2=status/connect;bgl=4");
        string source;
        string destination;
        string multiPointSource;
        string multiPointDestination;
        int initKeyLength;
        bool multipoint;
    submodules:
        switch: Switch {
            @display("p=156,144");
        }
        client01: Client {
            @display("p=52,49");
        }
        client02: Client {
            @display("p=48,241");
        }
        client03: Client {
            @display("p=272,51");
        }
        client04: Client {
            @display("p=275,227");
        }
    connections:
        client01.publicInterface <--> {  delay = 100ms; } <--> switch.fe01;
        client02.publicInterface <--> {  delay = 100ms; } <--> switch.fe02;
        client03.publicInterface <--> {  delay = 100ms; } <--> switch.fe03;
        client04.publicInterface <--> {  delay = 100ms; } <--> switch.fe04;
        client01.quantumInterface <--> {  delay = 100ms; } <--> switch.qu01;
        client02.quantumInterface <--> {  delay = 100ms; } <--> switch.qu02;
        client03.quantumInterface <--> {  delay = 100ms; } <--> switch.qu03;
        client04.quantumInterface <--> {  delay = 100ms; } <--> switch.qu04;
}
