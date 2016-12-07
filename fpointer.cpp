#include <iostream>
#include <map>

using namespace std;

class Card;
class CardController;

enum memFuncs {modulate_e, noise_e};

class Card
{
	friend class CardController;
public:
	typedef void(Card::*ptrToMemFunc)(void);
private:
	void callMemFunction(memFuncs mf_e)
	{
		(this->*(funcMap[mf_e]))();
	}
protected:
	static map<memFuncs, ptrToMemFunc> funcMap;
};

class ModemCard_t : public Card
{
public:
	ModemCard_t() {}
	void modulate() { cout << "modulate()" << endl;}
	static void Register()
	{
		funcMap[modulate_e] = (ptrToMemFunc)&ModemCard_t::modulate;
	}
};

class CardController
{
public:
	void doFunc(Card* c, memFuncs mf)
	{
		c->callMemFunction(mf);
	}
};

int main()
{
	ModemCard_t::Register();
	ModemCard_t mc;
	CardController cc;
	
	cc.doFunc(&mc, modulate_e);

	return 0;
}




































