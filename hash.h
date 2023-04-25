#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <cctype>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <math.h> 


typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
				std::vector<unsigned long long> w(5,0);
				std::string kcopy = k;
				// if(k.length()%6 != 0){
				// 	// if(k.length() > 6){
				// 	// 	//this part
				// 	// 	//std::cout << 6-(k.length()%6) << std::endl;
				// 	// 	kcopy.insert(6*(k.length()/6) ,6-(k.length()%6), 'a');//6-(k.length()%6)
				// 	// }else{
				// 	// 	kcopy.insert(6*(k.length()/6) ,6-k.length(), 'a');
				// 	// }
				// }

			while(kcopy.length()%6 != 0)
			{
				kcopy.insert(0,"a");
			}


				//else{
				// 	for(int i =  static_cast<int>(w.size()-1); i >= 0; i--){
				// 		for(int j = 5; j >= 0; j++){
				// 				w[i] += letterDigitToNumber(k.at(j)) * static_cast<int>(power(36,j));
				// 				//count--;
				// 		}
				// 	}
				// }
				//int powersofthirtysix = 60466176;
				int count = 0;//kcopy.length()-1
				// for(int i =  static_cast<int>(w.size()-1); i >= 0; i--){	
				for(int i = 5-(kcopy.length()/6); i <= 4; i++){	

						int powersofthirtysix = 60466176;
						for(int j = 0; j <= 5; j++){
								if(count >kcopy.length()-1){
									goto stop;
								}
								w[i] += letterDigitToNumber(kcopy.at(count)) * powersofthirtysix;
								count++;
								powersofthirtysix/=36;
						}
						std::cout<<"w["<<i<<"]: "<< w[i] << std::endl;
					}

			stop:
			HASH_INDEX_T h = 0;
			for(int i = 0; i <= 4; i++){
				h+= rValues[i] * w[i];
			}
			return h;

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
			// for(unsigned int i = k.size()-1; -1 < i; i--){
			// 		k[i] = tolower(k[i]);
			// 		if(k[i] >= 97 && k[i] <= 122){
			// 			//scale it down
			// 			k[i] = k[i] - 97;
			// 			temp.push_back(k[i]);
			// 		}else if(k[i] >= 30 && k[i] <= 39){
			// 			//scale it down
			// 			k[i] = k[i] - 30;
			// 			temp.push_back(k[i]);
			// 		}
			// 	}
			HASH_INDEX_T temp =0;
			letter = tolower(letter);
			if(letter >= 97 && letter <= 122){
					//scale it down
				 
					temp = letter - 97;
					return temp;
			}else if(letter >= 48 && letter <= 57){
				//scale it down
				temp = letter - 22;
				return temp;

			}
			return NULL;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
		HASH_INDEX_T power(int base, int exp) const{
			int ihateconst = 1;
			//HASH_INDEX_T r = base;
			std::vector<int> binary;
			while(exp != 0){
					if(exp%2 == 1){
						binary.push_back(1);
					}else{
						binary.push_back(0);
					}
					exp/=2;
			}
			
			for(unsigned int i = 0; i < binary.size();i++){
				if(binary[i] == 1){
					ihateconst*=pow(double(base),double(i));
				}
			}
			HASH_INDEX_T x = ihateconst;
			return x;
		}
};

#endif
