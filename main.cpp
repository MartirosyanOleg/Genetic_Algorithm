#include <iostream>
#include <ctime> 
#include <cstdlib> 

class Chromosome
{
public:
	Chromosome()
	{
		speed = (1 + rand() % 100) * 100;
		diameter = (1 + rand() % 100) * 0.01;
		viscosity = (1 + rand() % 100) * 0.00000001;
		countRe();
	}
	Chromosome(double speed, double diameter, double viscosity) : speed(speed), diameter(diameter), viscosity(viscosity)
	{
		countRe();
	}
	Chromosome(const Chromosome& src)
	{
		this->speed = src.speed;
		this->diameter = src.diameter;
		this->viscosity = src.viscosity;
		this->Re = src.Re;
		countRe();
	}
	~Chromosome() {}

	void setSpeed(double s)
	{
		speed = s;
		countRe();
	}

	void setDiameter(double d)
	{
		diameter = d;
		countRe();
	}
	void setViscosity(double v)
	{
		viscosity = v;
		countRe();
	}

	double getSpeed() { return speed; }
	double getDiameter() { return diameter; }
	double getViscosity() { return viscosity; }
	double getRe() { return Re; }


	void countRe()
	{
		Re = speed * diameter / viscosity;
	}

	bool operator> (const Chromosome& other)
	{
		return Re > other.Re;
	}
	bool operator< (const Chromosome& other)
	{
		return Re < other.Re;
	}
	friend std::ostream& operator<< (std::ostream& stream, const Chromosome& population);
	friend std::istream& operator>> (std::istream& stream, Chromosome& population);
	Chromosome& operator =(const Chromosome& other)
	{
		this->speed = other.speed;
		this->diameter = other.diameter;
		this->viscosity = other.viscosity;
		this->Re = other.Re;
		return *this;
	}
private:
	double speed, diameter, viscosity, Re;
};

void sortFamily(Chromosome& a, Chromosome& b, Chromosome& c);

int main()
{
	srand(time(0));
	const double RE_INF = 10e8;
	double bestRe = RE_INF;
	int popSize, maxIterations;
	double probCrossover, probMutation;
	std::cin >> popSize >> maxIterations >> probCrossover >> probMutation;
	Chromosome* chr = new Chromosome[popSize];

	for (int i = 0; bestRe > 1000 && i < maxIterations; i++)
	{

		std::cout << "Iteration number: " << i << std::endl << std::endl;
		std::cout << "Crossed Family: " << std::endl;

		for (int j = 0; j < popSize - 2; j += 3)
		{
			if ((rand() % 1000) * 0.001 < probCrossover)
			{
				sortFamily(chr[j], chr[j + 1], chr[j + 2]);
				chr[j + 2] = Chromosome(std::min(chr[j].getSpeed(), chr[j + 1].getSpeed()),
					std::min(chr[j].getDiameter(), chr[j + 1].getDiameter()),
					std::max(chr[j].getViscosity(), chr[j + 1].getViscosity()));
				std::cout << j << " ";
			}
		}


		std::cout << std::endl << "Mutating chromosomes: " << std::endl;

		for (int j = 0; j < popSize; j++)
		{
			if ((rand() % 1000) * 0.001 < probMutation)
			{
				int mutGen = rand() % 3;

				if (mutGen == 0)
				{
					chr[j].setSpeed(chr[j].getSpeed() / 2);
				}
				else if (mutGen == 1)
				{
					chr[j].setDiameter(chr[j].getSpeed() / 2);
				}
				else if (mutGen == 2)
				{
					chr[j].setViscosity(chr[j].getViscosity() * 2);
				}
				std::cout << j << " ";
			}
		}

		std::cout << std::endl;

		for (int j = 0; j < popSize; j++)
		{
			if (chr[j].getRe() < bestRe)
			{
				bestRe = chr[j].getRe();
			}
		}
		std::cout << "BestRe:" << std::endl << bestRe << std::endl;
		if (bestRe > 1000)
		{
			std::cout << "Adapted chromosome was not found" << std::endl << std::endl;
		}
		else
		{
			std::cout << "Adapted chromosome has been found:" << std::endl;
			for (int i = 0; i < popSize; i++)
			{
				if (chr[i].getRe() < 1000)
				{
					std::cout << "Chromosome number: " << i << std::endl;
					std::cout << "Speed: " << chr[i].getSpeed() << std::endl;
					std::cout << "Diameter: " << chr[i].getDiameter() << std::endl;
					std::cout << "Viscosity: " << chr[i].getViscosity() << std::endl;
					std::cout << std::endl;
					break;
				}
			}
		}
	}
	delete[] chr;
	return 0;
}

void sortFamily(Chromosome& a, Chromosome& b, Chromosome& c)
{
	if (a > b) std::swap(a, b);
	if (b > c) std::swap(b, c);
	if (a > c) std::swap(a, c);
}

std::ostream& operator << (std::ostream& stream, const Chromosome& population)
{
	stream << population.Re << " ";
	return stream;
}

std::istream& operator >> (std::istream& stream, Chromosome& population)
{
	stream >> population.Re;
	return stream;
}