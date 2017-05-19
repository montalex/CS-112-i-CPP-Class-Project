#ifndef INFOSV_VIRUS
#define INFOSV_VIRUS

#define VIRULENCE_PROFILE_SIZE 10

class Virus {
private:
	double virulence[VIRULENCE_PROFILE_SIZE];
	double amount;
	double growthRate;

public:
	Virus();
	Virus(const Virus& other);
	Virus(const double* virulence_profile);
};

#endif