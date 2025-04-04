#include "algorithms/modes/ECB.h"
#include "algorithms/modes/CBC.h"
#include "algorithms/modes/CMAC.h"
#include "utils/Utils.h"
#include <map>

int printUsage(const string& programName)
{
	cerr << "Usage: " << programName << " <mode: ECB|CBC> <encrypt|decrypt> -k <key_hex> [-iv <iv_hex>] -in <input_file> -out <output_file>\n";
	return 1;
}

void ECB_start(const string& action, const Key& key, const string& inData, string& outData)
{
	ECB ecb(key);

	if (action == "encrypt")
		ecb.Encrypt(inData, outData);
	else if (action == "decrypt")
		ecb.Decrypt(inData, outData);
}

void CBC_start(const string& action, const Key& key, const string& ivStr, const string& inData, string& outData)
{
	CBC cbc(key, State(ivStr));

	if (action == "encrypt")
		cbc.Encrypt(inData, outData);
	else if (action == "decrypt")
		cbc.Decrypt(inData, outData);
}

void CMAC_start(const Key& key, const string& inData, string& outData)
{
	CMAC cmac(key);
	outData = cmac.GenerateMAC(inData);
}

int main(int argc, char* argv[]) {
	// string modeStr = argv[1];
	// string actionStr = argv[2];
	// string keyStr, ivStr;
	// string inStr, outStr;

	// for (int i = 1; i < argc; ++i)
	// {
	// 	string arg = argv[i];

	// 	if (arg == "-k" && i + 1 < argc)
	// 		keyStr = argv[++i];
	// 	else if (arg == "-iv" && i + 1 < argc)
	// 		ivStr = argv[++i];
	// 	else if (arg == "-in" && i + 1 < argc)
	// 		inStr = argv[++i];
	// 	else if (arg == "-out" && i + 1 < argc)
	// 		outStr = argv[++i];
	// }

	// if (keyStr.empty() || inStr.empty() || outStr.empty())
	// 	return printUsage(argv[0]);

	// Key key(keyStr);

	// string inData = Utils::readFile(inStr);
	// string outData;

	// if (modeStr == "ECB" && ivStr.empty())
	// 	ECB_start(actionStr, key, inData, outData);
	// else if (modeStr == "CBC" && !ivStr.empty())
	// 	CBC_start(actionStr, key, ivStr, inData, outData);
	// else if (modeStr == "CMAC" && ivStr.empty())
	// 	CMAC_start(key, inData, outData);
	// else
	// 	return printUsage(argv[0]);

	// Utils::writeFile(outStr, outData);

	// return 0;

	string mode, action, keyStr, ivStr, message, outData;
    
    cout << "Choisir le mode (ECB, CBC, CMAC): ";
    cin >> mode;
    
    if (mode == "ECB" || mode == "CBC") {
        cout << "Quelle action ? (encrypt, decrypt): ";
        cin >> action;
    }
    
    cout << "Key (hex): ";
    cin >> keyStr;
    
    if (mode == "CBC") {
        cout << "Entrer IV (hex): ";
        cin >> ivStr;
    }
    
    cout << "Entrer message: ";
    cin.ignore();
    getline(cin, message);
    
    Key key(keyStr);
    
    cout << "Message original: " << message << endl;
    
    if (mode == "ECB") {
		ECB_start(action, key, message, outData);
		cout << "Resultat (ECB) :" << outData << endl;
	}
    else if (mode == "CBC") {
		CBC_start(action, key, ivStr, message, outData);
		cout << "Resultat (CBC) :" << outData << endl;
	} 
    else if (mode == "CMAC") {
		CMAC_start(key, message, outData);
		cout << "Resultat (CMAC) :" << outData << endl;
	}  
    else {
		cout << "Mode invalide!" << endl;
	}
        
    
    return 0;
}