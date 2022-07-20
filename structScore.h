#pragma once //https://stackoverflow.com/questions/33001923/redefinition-of-a-class-in-a-header-file 	
#include <cctype>
using namespace std;
			//This is to prevent the same code being included in every file where you include this header (double inclusion). 
			//This will essentially help out the pre-processor.

struct structScore{
public:
	structScore(){	}
	char m_nick[3];
	int m_points;
	structScore(char nick[3], int points){
		for (int i = 0; i < 3; i++)
		{
			this->m_nick[i]=nick[i];
		}
		
		this->m_points = points;
	}
		void uppernick(){
			for(int i=0;i<3;++i) { 
				m_nick[i] = toupper(m_nick[i]);
			}
		}
		bool operator<(structScore aux){
			if (this->m_points<aux.m_points)
			{
				return true;
			}
			return false;
		}
		bool operator>(structScore aux){
			if (this->m_points>aux.m_points)
			{
				return true;
			}
			return false;
		}
		
};
