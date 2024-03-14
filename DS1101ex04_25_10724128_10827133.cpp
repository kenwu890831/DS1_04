// 10724128 �d�t�� 10827133 �H���
// �i�u��j�V�i�sĶ�ﶵ�j�V�i�sĶ���j�Ŀ�i�sĶ�ɥ[�J�H�U�R�O�j
// �[�J�i-std=c++11�j �A�Y�i�B�@�C

#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <cmath>
#include <new>
#include <cmath>
#include <vector>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std ;
clock_t readStart, readEnd ;
clock_t sortStart, sortEnd ;
clock_t writeStart, writeEnd ;
double readDuration, sortDuration, writeDuration ;

struct AbortNode{ // �����M�� 
    int ID;
    int abort ; // �����ɨ� 
    int deley ; // ����ɶ� 
};

struct DoneNode{
    int ID;
    int departure ; // �����ɨ� 
    int deley ; // ����ɶ�
};

struct QueueNode{
    int ID;
    int arrival ;
    int duration ;
    int timeout ;
    QueueNode *next;
    QueueNode(){};
    QueueNode(int ID_input, int arrival_input, int duration_input, int timeout_input) {
         ID = ID_input ;
         arrival = arrival_input ;
         duration = duration_input ;
         timeout = timeout_input ;
    };
};

class newQueue{
private:
    QueueNode *first;
    QueueNode *back;
    int size;
public:
    newQueue():size(0){};
    void Push(int ID_input, int arrival_input, int duration_input, int timeout_input);
    void Pop();
    bool IsEmpty();
    QueueNode getFront();
    int getSize();
};

void newQueue::Push(int ID_input, int arrival_input, int duration_input, int timeout_input){

    if (IsEmpty()) {
        first = new QueueNode(ID_input, arrival_input,  duration_input, timeout_input);
        back = first;
        size++;
        return;
    }

    QueueNode *newNode = new QueueNode(ID_input, arrival_input,  duration_input, timeout_input);
    back->next = newNode;
    back = newNode;         // update back pointer
    size++;
}

void newQueue::Pop(){

    if (IsEmpty()) {
        cout << "Queue is empty.\n";
        return;
    }

    QueueNode *deletenode = first;
    first = first->next;    // update front pointer
    delete deletenode;
    deletenode = NULL;
    size--;
}

QueueNode newQueue::getFront(){
    QueueNode temp ;
    if (IsEmpty()) {
        cout << "Queue is empty.\n";
        return temp;
    }

    temp.ID = first -> ID ;
    temp.arrival =first -> arrival ;
    temp.duration = first -> duration ;
    temp.timeout =  first -> timeout ;
    return temp;
}

bool newQueue::IsEmpty(){

    return (size == 0);

}

int newQueue::getSize(){

    return size;
}

int getNum() {
	int temp ;
	string inputS ;
	bool isNum ;

	do {
		cin >> inputS ;
		isNum = true ;
		for ( int i = 0; ( i < inputS.length()) && ( isNum ) ; i++ )
		  if( ( inputS[i] > '9') || ( inputS[i] < '0') )
		    isNum = false ;
		if ( !isNum )
		  continue ;
		temp = strtoul( inputS.c_str(), NULL, 10 ) ;

		  break ;


	} while( true );// end do-while

	return temp ;
} // getNum()

class mission{
private:
    QueueNode temp;

    string inputString ;
    newQueue q ;
    int size ;
    string title ;
    vector<struct QueueNode> workList ; // ���Ȥ@�إߪ��u�@�C 
    vector<struct AbortNode> abortList ;
    vector<struct DoneNode> doneList ;
public:
    mission(){};
    void readTheFile() ; // Ū��
    void shellSort() ; // �ƺ��Ƨ�
    void missionTwo() ; // �����C���� 
    void writeTheFile() ; // ��X�Ƨǧ����ɮ� 
    void readTheSortedFile() ; // Ū�ƧǦn����
};

void mission::readTheFile() { // Ū��
    int input = 1 , number = 0 ;
    int ID_input, arrival_input, duration_input, timeout_input ;
    int count = 0 ;
  	cout << endl << "Input a file number (e.g., 401, 402, ...): " ;
  	input = getNum() ; // Ū�J�ɦW
  	inputString = to_string( input ) ; // �Nint�ɦW�নstring
  	fstream theFile;
  	readStart = clock() ;
  	theFile.open( "input"+inputString+".txt" ); // �}�ҫ��w�ɮ�

  	if ( theFile.is_open() ) { // �p�G�����}�ɮ�
    	getline( theFile, title ) ; // Ū�J�Ĥ@�� 
    	while (theFile >> number) {
            count ++ ;
            if ( count == 1 ) { // �u�@�s��OID  
                temp.ID = number ; 
            }
            else if ( count == 2) { // �i�J�ɨ�Arrival
                temp.arrival = number ; 
            }
            else if ( count == 3 ) { // �u�@�Ӯ�Duration
                temp.duration = number ;
            }
            else if ( count == 4 ) {
                temp.timeout = number ; // �O�ɮɨ�Timeout
                workList.push_back(temp);
                count = 0 ;
            }
        }

    	theFile.close();
    	readEnd = clock() ;
        readDuration = (double)( readEnd - readStart ) ;
        readDuration /= 1000 ; // �O��Ū�ɮɶ� 
    } // if
    else {
        cout << "input" +inputString + ".txt does not exist!" << endl ;
    }

} // readTheFile

void mission::shellSort() { // �ƺ��Ƨ�
    sortStart = clock() ;
    size = workList.size() ;
    for (int gap = size/2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i += 1) {
            QueueNode temp = workList[ i ];
            int j;
            // �̷Ӷi�J�ɨ�arrival���W�ƧǡA�ۦP�h�H�u�@�s��ID���W�Ƨ� 
            for ( j = i ;  j >= gap && ( ( workList[j - gap].arrival > temp.arrival ) || ( workList[j - gap].arrival == temp.arrival && workList[j - gap].ID > temp.ID) )  ;  j -= gap ) {
                workList[ j ] = workList[ j - gap ];
            }
            workList[ j ] = temp;
        }
    }

    sortEnd = clock() ;
    sortDuration = (double)( sortEnd - sortStart ) ;
    sortDuration /= 1000 ; // �����ƧǮɶ� 

} // shellSort()

void mission::readTheSortedFile() { // Ū�ƧǦn����
    int input = 1 , number = 0 ;
    int ID_input, arrival_input, duration_input, timeout_input ;
    int count = 0 ;
  	cout << endl << "Input a file number (e.g., 401, 402, ...): " ;
  	input = getNum() ; // Ū�J�ɦW
  	cout << endl ;
  	inputString = to_string( input ) ; // �Nint�ɦW�নstring
  	fstream theFile;
  	readStart = clock() ;
  	theFile.open( "sorted"+inputString+".txt" ); // �}�ҫ��w�ɮ�

  	if ( theFile.is_open() ) { // �p�G�����}�ɮ�
    	getline( theFile, title ) ; // Ū�J�Ĥ@�檺��b�e&�a�b��
    	while (theFile >> number) {
            count ++ ;
            if ( count == 1 ) {
                temp.ID = number ;
            }
            else if ( count == 2) {
                temp.arrival = number ;
            }
            else if ( count == 3 ) {
                temp.duration = number ;
            }
            else if ( count == 4 ) {
                temp.timeout = number ;
                workList.push_back(temp);
                count = 0 ;
            }

        }
        size = workList.size() ;
    	theFile.close();
    	readEnd = clock() ;
        readDuration = (double)( readEnd - readStart ) ;
        readDuration /= 1000 ; // �O��Ū�ɮɶ� 
        
    } // if
    else {
        cout << "sorted" +inputString + ".txt does not exist!" << endl ;
    }

} // readTheSortedFile() 

void mission::writeTheFile() { // ��X�Ƨǧ����ɮ� 
    writeStart = clock() ;
    fstream newFile;
    newFile.open("sorted"+inputString+".txt", ios::out);
    // Write to the file
    int count = 0 ;
    int number = 1 ;

    newFile << title << endl ;
    cout << "\t" << "OID" << "\t" << "Arrival" << "\t" << "Duration" << "\t" << "TimeOut" << endl ;
   	while ( count < size ) { // �̧ǱN�ƧǦn���g�J�ɮ� 
   			cout << "(" << number << ")" << "\t" ;
            newFile << workList.at(count).ID << "\t" ;
            cout << workList.at(count).ID << "\t" ;
            newFile << workList.at(count).arrival << "\t" ;
            cout << workList.at(count).arrival << "\t" ;
            newFile << workList.at(count).duration << "\t" ;
            cout << workList.at(count).duration << "\t" ;
            newFile <<  workList.at(count).timeout << endl ;
            cout <<  workList.at(count).timeout << endl ;
           	count ++ ;
           	number ++ ;
    }

    newFile.close();
    writeEnd = clock() ;
    writeDuration =  (double)(writeEnd - writeStart) ;
    writeDuration = writeDuration / 1000 ; // ������X�ɮת��ɶ�  
    workList.clear(); // �M�Ťu�@�C 
} // writeTheFile() 

void mission::missionTwo() { //  �}�l��C����  
    cout << "The simulation is running..." << endl ;
    fstream newFile ;
    int arrivalTime = 0 ;
    newFile.open("output"+inputString+".txt", ios::out);
    int count = 1 ;
    int time = workList.at(0).arrival + workList.at(0).duration ; // �ثe�ɶ�:�����Ĥ@���u�@�᪺�ɶ� 
    DoneNode doneTemp ; // �i�����M��j 
    AbortNode abortTemp ; // �i�����M��j 
    vector<struct QueueNode> working ; // �i���b�����u�@�j 
    float totalDelay = 0.0 ; // �`���� 
    float doneCount = 1.0 ; // �������u�@�� 
    QueueNode returnTemp ;
    doneTemp.ID = workList.at(0).ID ;
    doneTemp.departure =  workList.at(0).arrival + workList.at(0).duration ;
    doneTemp.deley = 0 ;
    doneList.push_back(doneTemp); // �N�Ĥ@���u�@�[��i�����M��j 
    bool isEnd = false, isLast = false ;
       while ( !isEnd ) {
        if ( q.getSize() < 3 && !isLast) { // ��C�����u�@���j��T�� && �o���O�u�@�C���̫�@���u�@
            while ( !q.IsEmpty() && ( time > workList.at(count).timeout ) && (!working.empty())) { // �p�G��C�O�Ū� && ��e�ɶ��j���e�u�@���O�ɮɨ�timeout(�N��W�ɤF) && ���i���b�����u�@�j
                    abortTemp.ID =working.at(0).ID ;
                    abortTemp.abort =time ;
                    abortTemp.deley =time - working.at(0).arrival ;
                    totalDelay = totalDelay + abortTemp.deley ;
                    abortList.push_back(abortTemp); // �N�����u�@�[��i�����M��j 
                    working.clear() ; // �M�ši���b�����u�@�j  
                    returnTemp = q.getFront() ; // �N�Ʀb��C�̫e�u�@�����X  
                    working.push_back( returnTemp) ; // �[���i���b�����u�@�j 
                    q.Pop() ;
                    count++ ;
            }
            q.Push( workList.at(count).ID, workList.at(count).arrival, workList.at(count).duration, workList.at(count).timeout ) ; // �N��e�u�@�[���C�� 
            if ( count == size -1 ) // �p�G�o�O�u�@�C���̫�@���u�@  
                isLast = true ;
            if ( count != size -1) // �p�G�o���O�u�@�C���̫�@���u�@ 
            	count++ ; // �~��U�@��  

        }
        else if ( workList.at(count).arrival < time && !isLast ) { //  �u�@����F�ɶ�arrival�p��ثe�ɶ�(�N��W�ɤF) && �o���O�u�@�C���̫�@���u�@
            abortTemp.ID =workList.at(count).ID ;
            abortTemp.abort =workList.at(count).arrival ;
            abortTemp.deley = 0 ;
            abortList.push_back(abortTemp); // �N�����u�@�[��i�����M��j 
            if ( count == size -1 ) // �p�G�o�O�u�@�C���̫�@���u�@ 
                isLast = true ;
            if ( count != size -1) // �p�G�o���O�u�@�C���̫�@���u�@
            	count++ ; // �~��U�@�� 
        }
        else if ( working.empty() && !isEnd )  { // �S���u�@���b�� && �٨S���������u�@
                returnTemp = q.getFront() ; // �N�Ʀb��C�̫e�u�@�����X 
                working.push_back( returnTemp) ; // �[���i���b�����u�@�j 
                q.Pop() ; 
                while ( !q.IsEmpty() && ( time >= working.at(0).timeout )) { // �p�G��C���O�Ū� && �ثe�ɶ��j��i���b�����u�@�j���O�ɮɨ�timeout(�N��W�ɤF)
                    abortTemp.ID =working.at(0).ID ;
                    abortTemp.abort =time ;
                    abortTemp.deley =time - working.at(0).arrival ;
                    totalDelay = totalDelay + abortTemp.deley ;
                    abortList.push_back(abortTemp); // �N�����u�@�[��i�����M��j  
                    working.clear() ; // �M�ši���b�����u�@�j 
                    returnTemp = q.getFront() ; // �N�Ʀb��C�̫e�u�@�����X
                    working.push_back( returnTemp ) ; // �[���i���b�����u�@�j
                    q.Pop() ;
                }

                if( working.at(0).arrival > time) time = working.at(0).arrival ; // �p�G�i���b�����u�@�j���O�ɮɨ�timeout�j��ثe�ɶ�(�N��S���W��)�A�N�N�ثe�ɶ��]���i���b�����u�@�j����F�ɨ�arrival
                arrivalTime = time ;
        }
        else { // �P�_�u�@�Ӯɪ����� 
            int duration = working.at(0).duration; // �q�i���b�����u�@�j���u�@�Ӯ�duration�}�l 
            while ( !working.empty()) { // �p�G���i���b�����u�@�j

                duration -- ;
                if ( time >= working.at(0).timeout  ) { // �ثe�ɶ��j�󵥩�i���b�����u�@�j���O�ɮɨ�timeout(�N��W�ɤF)
                    abortTemp.ID =working.at(0).ID ;
                    abortTemp.abort =time ;
                    abortTemp.deley =time - working.at(0).arrival ;
                    totalDelay = totalDelay + abortTemp.deley ;
                    abortList.push_back(abortTemp); // �N�����u�@�[��i�����M��j
                    working.clear() ; // �M�ši���b�����u�@�j 
                    break ;
                }
                else if ( duration == 0 ) { // �p�G�u�@�Ӯ�duration��0(�N�����F) 
                    doneTemp.ID =working.at(0).ID ;
                    time++ ;
                    doneTemp.departure =time ;
                    doneTemp.deley = arrivalTime - working.at(0).arrival;
                    totalDelay = totalDelay + doneTemp.deley ;
                    doneList.push_back(doneTemp); // �N�����u�@�[��i�����M��j
                    doneCount++ ;
                    working.clear() ; // �M�ši���b�����u�@�j  
                    break ;
                }
            time++ ;
            } // while
        }

        if ( q.IsEmpty() && working.empty() && count == size -1) // �p�G��C�O�Ū� && �u�@�C�]�O�Ū� && �u�@�C�쩳�F 
            isEnd = true ; // �N������u�@�������F 
            
    }

    count = 0 ;
    int abortSize = abortList.size() ;
    newFile <<  "        [Abort Jobs]" << endl ;
    newFile <<  "        OID \tAbort\tDelay" << endl ;
    while ( count < abortSize) {
        newFile <<  "[" << count + 1 << "]\t"<< abortList.at(count).ID << "\t"<< abortList.at(count).abort << "\t" << abortList.at(count).deley<< endl ;
        count ++ ;
    } // ��X�i�����M��j

    count = 0 ;
    int doneSize = doneList.size() ;
    newFile <<  "       [Jobs Done]" << endl ;
    newFile <<  "        OID \tDeparture\tDelay" << endl ;
    while ( count < doneSize) {
        newFile <<  "[" << count + 1 << "]\t"<< doneList.at(count).ID << "\t"<< doneList.at(count).departure << "\t" << doneList.at(count).deley<< endl ;
        count ++ ;
    } // ��X�i�����M��j

    newFile <<  "\n[Average Delay]\t" << fixed  <<  setprecision(2)<< totalDelay/size << " ms"<< endl ;
    newFile <<  "[Success Rate]\t" << fixed  <<  setprecision(2)<<  doneCount/size*100 << " %"<< endl ;
    cout << "See output"+ inputString+ ".txt" << endl ;
    workList.clear() ;
    doneList.clear() ;
    abortList.clear() ;
} // missionTwo()

int main(){
    newQueue q ;
    mission m ;
   int command = 0 ; // user command
  do {

  	cout << endl << "*** Arithmetic Expression Evaluator ***" ;
  	cout << endl << "* 0. Quit                             *" ;
  	cout << endl << "* 1. Sort a file                      *" ;
  	cout << endl << "* 2. Simulate one FIFO queue          *" ;
  	cout << endl << "***************************************" ;
  	cout << endl << "Input a command( 0, 1, 2 ) : " ;
  	cin >> command ; // get the command
  	switch(command){
		case 0 : break ; //���X�A����

  		case 1 : // �H���w��k�O�رƧ��� 
            m.readTheFile() ; // Ū�� 
            m.shellSort() ; // �ƺ��Ƨ� 
            m.writeTheFile() ; // ���� 
            cout << endl ;
            cout << "Reading Data: " << readDuration << " sec" << endl ; // ��XŪ�ɮɶ� 
            cout << "Sorting Data: " << sortDuration << " sec" << endl ; // ��X�ƺ��ƧǮɶ� 
            cout << "Writing Data: " << writeDuration << " sec" << endl ; // ��X���ɮɶ� 
            break ;
  		case 2 : // ��@CPU����C���� 
            m.readTheSortedFile() ; // Ū�ƧǦn���� 
            m.missionTwo() ; //  �}�l��C���� 
  			break ;

  		default :
			cout << endl << "command does not exist !!" << endl ;
  			break ;

	} // end switch

  } while ( command != 0 ) ;

  system( "pause") ; // pause the display
  return 0 ;
}
