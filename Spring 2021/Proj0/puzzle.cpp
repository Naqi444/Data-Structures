#include "puzzle.h"
Puzzle::Puzzle(int size){
    // *************************************
    // Implement the alternative constructor
    // *************************************
    if(size<0){
        m_size = 0;
    }
    m_size = size;
    makeMem();
    fill();
}
Puzzle::~Puzzle(){
    clear();
}
void Puzzle::clear(){
    // ***************************
    // Implement clear() function
    // ***************************
    for(int i = 0;i < m_size;i++){
		delete [] m_table[i];
	}
	delete [] m_table;

	m_table = nullptr;
	m_size = 0;
}
void Puzzle::makeMem(){
    // ****************************
    // Implement makeMem() function
    // ****************************
    if(this->m_size>0){
        m_table = new char *[m_size];
        for(int i=0 ; i<m_size ; ++i)
        {
            m_table[i] = new char[m_size]; // allocate memory for columns in each row
        }
    }else{
        m_table = nullptr;
    }
}
Puzzle::Puzzle(const Puzzle& rhs){
    // ***************************
    // Implement copy constructor
    // ***************************
    m_size = std::max(rhs.m_size,0);
    this->m_size = rhs.m_size;
    makeMem(); 
    for (int i=0;i<m_size;i++){
        for(int j=0;j<m_size;j++){
            m_table[i][j] = rhs.m_table[i][j];
        }
    }
}
const Puzzle& Puzzle::operator=(const Puzzle& rhs){
    // *****************************
    // Implement assignment operator
    // *****************************
    if(this!=&rhs){
        clear();

        m_size = std::max(rhs.m_size,0);
        makeMem();

        for(int i = 0;i < m_size;i++){
			for(int j = 0;j < m_size;j++){
				m_table[i][j] = rhs.m_table[i][j];
			}
		}
        return *this;
    }
}
void Puzzle::dump(){
    if (m_size > 0){
        int i=0;
        int j=0;
        while(i<m_size){
            while(j<m_size){
                cout << m_table[i][j] << " ";
                j++;
            }
            cout << endl;
            j=0;
            i++;
        }
        cout << endl;
    }
}
void Puzzle::fill(){
    srand(time(NULL));//create the seed value using the current time
    int i=0;
    int j=0;
    while(i<m_size){
        while(j<m_size){
            m_table[i][j] = ALPHA[rand() % MAX];//find a random char from the chars list
            j++;
        }
        j=0;
        i++;
    }
}
