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
// @author Faisal Saleem
// @date April 03, 2019
// 

module Switch
{
    // Quatnum Key Distribution switch
    // Uses BB84 protocol to transfer quantum states between clients.
    parameters:
        // Display Paremeters (Color, Grid, Image etc)
        @display("bgb=441,711,#ECFFEC;i=abstract/switch;is=n;i2=status/green;bgtt=Quantum Key Distribution Switch");
    gates:
        inout fe01;		// FastEthernet 01
        inout fe02;		// FastEthernet 02;
        inout fe03;		// FastEthernet 03;
        inout fe04;		// FastEthernet 04;
        inout qu01;		// QuantumInterface 01;
        inout qu02;		// QuantumInterface 02;
        inout qu03;		// QuantumInterface 03;
        inout qu04;		// QuantumInterface 04;
    submodules:
        processor: Processor {
            @display("p=71,342;is=vl");
        }
        f01: SwitchPublicInterface {
            @display("p=51,657");
        }
        f02: SwitchPublicInterface {
            @display("p=169,657");
        }
        f03: SwitchPublicInterface {
            @display("p=278,657");
        }
        f04: SwitchPublicInterface {
            @display("p=388,657");
        }
        q01: SwitchQuantumInterface {
            @display("p=51,47");
        }
        q02: SwitchQuantumInterface {
            @display("p=169,47");
        }
        q03: SwitchQuantumInterface {
            @display("p=278,47");
        }
        q04: SwitchQuantumInterface {
            @display("p=388,47");
        }
        processingQueue: ProcessingQueue {
            @display("p=82,496;is=l");
        }
        quantumStatesQueue: QuantumStatesQueue {
            @display("p=176,202;is=l");
        }
        processedQueue: QuantumStatesQueue {
            @display("p=347,496;is=l");
        }
    connections:
        fe01 <--> f01.publicChannelCommunication;
        fe02 <--> f02.publicChannelCommunication;
        fe03 <--> f03.publicChannelCommunication;
        fe04 <--> f04.publicChannelCommunication;
        qu01 <--> q01.quantumChannelCommunication;
        qu02 <--> q02.quantumChannelCommunication;
        qu03 <--> q03.quantumChannelCommunication;
        qu04 <--> q04.quantumChannelCommunication;
        processingQueue.outToProcessor --> processor.jobsIn;
        quantumStatesQueue.outToInterface01 --> q01.quantumInterfaceStatus;
        quantumStatesQueue.outToInterface02 --> q02.quantumInterfaceStatus;
        quantumStatesQueue.outToInterface03 --> q03.quantumInterfaceStatus;
        quantumStatesQueue.outToInterface04 --> q04.quantumInterfaceStatus;
        f01.jobsToProcessor --> processingQueue.inFromInterface01;
        f02.jobsToProcessor --> processingQueue.inFromInterface02;
        f03.jobsToProcessor --> processingQueue.inFromInterface03;
        f04.jobsToProcessor --> processingQueue.inFromInterface04;
        processedQueue.outToInterface01 --> f01.processedJobs;
        processedQueue.outToInterface02 --> f02.processedJobs;
        processedQueue.outToInterface03 --> f03.processedJobs;
        processedQueue.outToInterface04 --> f04.processedJobs;
        processor.quantumInterfaceStatusOut --> quantumStatesQueue.inFromProcessor;
        processor.jobsOut --> processedQueue.inFromProcessor;
}

