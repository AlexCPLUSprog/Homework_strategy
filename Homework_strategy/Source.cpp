#include <iostream>
#include <memory>

class ITruck {
public:
	virtual void use_vehicle() = 0;
	virtual ~ITruck() {}
};

class Train : public ITruck {
public:
	void use_vehicle() override {
		std::cout << "Используется поезд\n";
	}
};

class Ship : public ITruck {
public:
	void use_vehicle() override {
		std::cout << "Используется корабль\n";
	}
};

class IStock {
public:
	virtual void placement() = 0;
	virtual ~IStock() {}
};

class Hangar :public IStock {
public:
	Hangar(std::shared_ptr<ITruck> truck) :_truck(truck) {}
	
	void placement() override {
		_truck->use_vehicle();
		std::cout << "Используется ангар\n";
	}
private:
	std::shared_ptr<ITruck> _truck;
};

class Barge : public IStock {
public:
	Barge(std::shared_ptr<ITruck> truck) :_truck(truck) {}
	
	void placement()override {
		_truck->use_vehicle();
		std::cout << "Используется баржа\n";
	}
private:
	std::shared_ptr<ITruck> _truck;
};

class Report {
public:
	Report(std::shared_ptr <IStock> stock) : _stock(stock) {}
	void report_car() {
		_stock->placement();
	}
private:
	std::shared_ptr <IStock> _stock;
};

int main() {
	setlocale(LC_ALL, "ru");

	std::string important_word;
	std::shared_ptr<ITruck> truck;
	std::shared_ptr<IStock> stock;

	std::cout << "Введите транспорт (train,ship):";
	std::cin >> important_word;

	if (important_word == "train")
		truck = std::make_shared<Train>();
	else if (important_word == "ship")
		truck = std::make_shared<Ship>();

	
	std::cout << "Введите место хранения груза (hangar,barge):";
	std::cin >> important_word;

	if (important_word == "hangar")
		stock = std::make_shared<Hangar>(truck);
	else if (important_word == "barge")
		stock = std::make_shared<Barge>(truck);

	Report rep(stock);
	rep.report_car();
	
}