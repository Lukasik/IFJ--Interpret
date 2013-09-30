//HLAVICKA PRO MODUL CHYBOVYCH HLASENI

//prototyp funkce
void printError(int errorCode, int returnCode);

// chybove kody -- pro indexy errorMessage
enum errs
{
	ALLOCERROR,
};

// navratove kody programu
enum returns
{
	INTERPRETERROR=99,
};

