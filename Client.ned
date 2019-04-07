
module Client
{
    parameters:
        @display("bgb=541,543,#ECFFEC;i=block/telnet;is=n;i2=status/green;bgtt=Quantum Key Distribution Switch");
        string name;
    gates:
        inout publicInterface;
        inout quantumInterface;

    submodules:
        clientPublicInterface: ClientPublicInterface {
            @display("p=482,503");
        }
        clientQuantumInterface: ClientQuantumInterface {
            @display("p=474,201");
        }
        DL: ClientFilterDL {
            @display("p=225,52");
        }
        DR: ClientFilterDR {
            @display("p=332,52;t=/");
        }
        H: ClientFilterH {
            @display("p=225,162;t=--");
        }
        V: ClientFilterV {
            @display("p=332,240;t=|");
        }
        quantumStatesGenerator: QuantumStatesGenerator {
            @display("p=64,201");
        }
        clientProcessor: ClientProcessor {
            @display("p=64,502");
        }
        clientFilterDiagonal: ClientFilterDiagonal {
            @display("p=225,356;t=X");
        }
        clientFilterStraight: ClientFilterStraight {
            @display("p=332,356;t=+");
        }
    connections:
        clientPublicInterface.externalCommunication <--> publicInterface;
        clientQuantumInterface.quantumChannelCommunication <--> quantumInterface;
        DL.polarizedLight --> clientQuantumInterface.dl;
        DR.polarizedLight --> clientQuantumInterface.dr;
        H.polarizedLight --> clientQuantumInterface.h;
        V.polarizedLight --> clientQuantumInterface.v;
        clientProcessor.publicInterfaceCommunication <--> clientPublicInterface.processorCommunication;
        quantumStatesGenerator.DL --> DL.unpolarizedLight;
        quantumStatesGenerator.DR --> DR.unpolarizedLight;
        quantumStatesGenerator.H --> H.unpolarizedLight;
        quantumStatesGenerator.V --> V.unpolarizedLight;
        clientProcessor.quantumInterfaceCommunication <--> quantumStatesGenerator.processorCommunication;
        clientQuantumInterface.diagonal --> clientFilterDiagonal.polarizedLightIn;
        clientQuantumInterface.flat --> clientFilterStraight.polarizedLightIn;
        clientFilterDiagonal.polarizedLightOut --> quantumStatesGenerator.Diagonal;
        clientFilterStraight.polarizedLightOut --> quantumStatesGenerator.Straight;
}

