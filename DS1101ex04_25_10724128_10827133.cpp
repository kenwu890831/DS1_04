// 10724128 吳宇哲 10827133 鄧梓岑
// 【工具】–【編譯選項】–【編譯器】勾選【編譯時加入以下命令】
// 加入【-std=c++11】 ，即可運作。

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

struct AbortNode{ // 取消清單 
    int ID;
    int abort ; // 取消時刻 
    int deley ; // 延遲時間 
};

struct DoneNode{
    int ID;
    int departure ; // 完成時刻 
    int deley ; // 延遲時間
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
    vector<struct QueueNode> workList ; // 任務一建立的工作列 
    vector<struct AbortNode> abortList ;
    vector<struct DoneNode> doneList ;
public:
    mission(){};
    void readTheFile() ; // 讀檔
    void shellSort() ; // 希爾排序
    void missionTwo() ; // 執行佇列模擬 
    void writeTheFile() ; // 輸出排序完的檔案 
    void readTheSortedFile() ; // 讀排序好的檔
};

void mission::readTheFile() { // 讀檔
    int input = 1 , number = 0 ;
    int ID_input, arrival_input, duration_input, timeout_input ;
    int count = 0 ;
  	cout << endl << "Input a file number (e.g., 401, 402, ...): " ;
  	input = getNum() ; // 讀入檔名
  	inputString = to_string( input ) ; // 將int檔名轉成string
  	fstream theFile;
  	readStart = clock() ;
  	theFile.open( "input"+inputString+".txt" ); // 開啟指定檔案

  	if ( theFile.is_open() ) { // 如果有打開檔案
    	getline( theFile, title ) ; // 讀入第一行 
    	while (theFile >> number) {
            count ++ ;
            if ( count == 1 ) { // 工作編號OID  
                temp.ID = number ; 
            }
            else if ( count == 2) { // 進入時刻Arrival
                temp.arrival = number ; 
            }
            else if ( count == 3 ) { // 工作耗時Duration
                temp.duration = number ;
            }
            else if ( count == 4 ) {
                temp.timeout = number ; // 逾時時刻Timeout
                workList.push_back(temp);
                count = 0 ;
            }
        }

    	theFile.close();
    	readEnd = clock() ;
        readDuration = (double)( readEnd - readStart ) ;
        readDuration /= 1000 ; // 記錄讀檔時間 
    } // if
    else {
        cout << "input" +inputString + ".txt does not exist!" << endl ;
    }

} // readTheFile

void mission::shellSort() { // 希爾排序
    sortStart = clock() ;
    size = workList.size() ;
    for (int gap = size/2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i += 1) {
            QueueNode temp = workList[ i ];
            int j;
            // 依照進入時刻arrival遞增排序，相同則以工作編號ID遞增排序 
            for ( j = i ;  j >= gap && ( ( workList[j - gap].arrival > temp.arrival ) || ( workList[j - gap].arrival == temp.arrival && workList[j - gap].ID > temp.ID) )  ;  j -= gap ) {
                workList[ j ] = workList[ j - gap ];
            }
            workList[ j ] = temp;
        }
    }

    sortEnd = clock() ;
    sortDuration = (double)( sortEnd - sortStart ) ;
    sortDuration /= 1000 ; // 紀錄排序時間 

} // shellSort()

void mission::readTheSortedFile() { // 讀排序好的檔
    int input = 1 , number = 0 ;
    int ID_input, arrival_input, duration_input, timeout_input ;
    int count = 0 ;
  	cout << endl << "Input a file number (e.g., 401, 402, ...): " ;
  	input = getNum() ; // 讀入檔名
  	cout << endl ;
  	inputString = to_string( input ) ; // 將int檔名轉成string
  	fstream theFile;
  	readStart = clock() ;
  	theFile.open( "sorted"+inputString+".txt" ); // 開啟指定檔案

  	if ( theFile.is_open() ) { // 如果有打開檔案
    	getline( theFile, title ) ; // 讀入第一行的橫軸寬&縱軸長
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
        readDuration /= 1000 ; // 記錄讀檔時間 
        
    } // if
    else {
        cout << "sorted" +inputString + ".txt does not exist!" << endl ;
    }

} // readTheSortedFile() 

void mission::writeTheFile() { // 輸出排序完的檔案 
    writeStart = clock() ;
    fstream newFile;
    newFile.open("sorted"+inputString+".txt", ios::out);
    // Write to the file
    int count = 0 ;
    int number = 1 ;

    newFile << title << endl ;
    cout << "\t" << "OID" << "\t" << "Arrival" << "\t" << "Duration" << "\t" << "TimeOut" << endl ;
   	while ( count < size ) { // 依序將排序好的寫入檔案 
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
    writeDuration = writeDuration / 1000 ; // 紀錄輸出檔案的時間  
    workList.clear(); // 清空工作列 
} // writeTheFile() 

void mission::missionTwo() { //  開始佇列模擬  
    cout << "The simulation is running..." << endl ;
    fstream newFile ;
    int arrivalTime = 0 ;
    newFile.open("output"+inputString+".txt", ios::out);
    int count = 1 ;
    int time = workList.at(0).arrival + workList.at(0).duration ; // 目前時間:完成第一項工作後的時間 
    DoneNode doneTemp ; // 【完成清單】 
    AbortNode abortTemp ; // 【取消清單】 
    vector<struct QueueNode> working ; // 【正在做的工作】 
    float totalDelay = 0.0 ; // 總延遲 
    float doneCount = 1.0 ; // 完成的工作數 
    QueueNode returnTemp ;
    doneTemp.ID = workList.at(0).ID ;
    doneTemp.departure =  workList.at(0).arrival + workList.at(0).duration ;
    doneTemp.deley = 0 ;
    doneList.push_back(doneTemp); // 將第一項工作加到【完成清單】 
    bool isEnd = false, isLast = false ;
       while ( !isEnd ) {
        if ( q.getSize() < 3 && !isLast) { // 佇列內的工作不大於三個 && 這不是工作列的最後一項工作
            while ( !q.IsEmpty() && ( time > workList.at(count).timeout ) && (!working.empty())) { // 如果佇列是空的 && 當前時間大於當前工作的逾時時刻timeout(代表超時了) && 有【正在做的工作】
                    abortTemp.ID =working.at(0).ID ;
                    abortTemp.abort =time ;
                    abortTemp.deley =time - working.at(0).arrival ;
                    totalDelay = totalDelay + abortTemp.deley ;
                    abortList.push_back(abortTemp); // 將此項工作加到【取消清單】 
                    working.clear() ; // 清空【正在做的工作】  
                    returnTemp = q.getFront() ; // 將排在佇列最前工作的取出  
                    working.push_back( returnTemp) ; // 加為【正在做的工作】 
                    q.Pop() ;
                    count++ ;
            }
            q.Push( workList.at(count).ID, workList.at(count).arrival, workList.at(count).duration, workList.at(count).timeout ) ; // 將當前工作加到佇列中 
            if ( count == size -1 ) // 如果這是工作列的最後一項工作  
                isLast = true ;
            if ( count != size -1) // 如果這不是工作列的最後一項工作 
            	count++ ; // 繼續下一個  

        }
        else if ( workList.at(count).arrival < time && !isLast ) { //  工作的抵達時間arrival小於目前時間(代表超時了) && 這不是工作列的最後一項工作
            abortTemp.ID =workList.at(count).ID ;
            abortTemp.abort =workList.at(count).arrival ;
            abortTemp.deley = 0 ;
            abortList.push_back(abortTemp); // 將此項工作加到【取消清單】 
            if ( count == size -1 ) // 如果這是工作列的最後一項工作 
                isLast = true ;
            if ( count != size -1) // 如果這不是工作列的最後一項工作
            	count++ ; // 繼續下一個 
        }
        else if ( working.empty() && !isEnd )  { // 沒有工作正在做 && 還沒完成全部工作
                returnTemp = q.getFront() ; // 將排在佇列最前工作的取出 
                working.push_back( returnTemp) ; // 加為【正在做的工作】 
                q.Pop() ; 
                while ( !q.IsEmpty() && ( time >= working.at(0).timeout )) { // 如果佇列不是空的 && 目前時間大於【正在做的工作】的逾時時刻timeout(代表超時了)
                    abortTemp.ID =working.at(0).ID ;
                    abortTemp.abort =time ;
                    abortTemp.deley =time - working.at(0).arrival ;
                    totalDelay = totalDelay + abortTemp.deley ;
                    abortList.push_back(abortTemp); // 將此項工作加到【取消清單】  
                    working.clear() ; // 清空【正在做的工作】 
                    returnTemp = q.getFront() ; // 將排在佇列最前工作的取出
                    working.push_back( returnTemp ) ; // 加為【正在做的工作】
                    q.Pop() ;
                }

                if( working.at(0).arrival > time) time = working.at(0).arrival ; // 如果【正在做的工作】的逾時時刻timeout大於目前時間(代表沒有超時)，就將目前時間設為【正在做的工作】的抵達時刻arrival
                arrivalTime = time ;
        }
        else { // 判斷工作耗時的部分 
            int duration = working.at(0).duration; // 從【正在做的工作】的工作耗時duration開始 
            while ( !working.empty()) { // 如果有【正在做的工作】

                duration -- ;
                if ( time >= working.at(0).timeout  ) { // 目前時間大於等於【正在做的工作】的逾時時刻timeout(代表超時了)
                    abortTemp.ID =working.at(0).ID ;
                    abortTemp.abort =time ;
                    abortTemp.deley =time - working.at(0).arrival ;
                    totalDelay = totalDelay + abortTemp.deley ;
                    abortList.push_back(abortTemp); // 將此項工作加到【取消清單】
                    working.clear() ; // 清空【正在做的工作】 
                    break ;
                }
                else if ( duration == 0 ) { // 如果工作耗時duration為0(代表做完了) 
                    doneTemp.ID =working.at(0).ID ;
                    time++ ;
                    doneTemp.departure =time ;
                    doneTemp.deley = arrivalTime - working.at(0).arrival;
                    totalDelay = totalDelay + doneTemp.deley ;
                    doneList.push_back(doneTemp); // 將此項工作加到【完成清單】
                    doneCount++ ;
                    working.clear() ; // 清空【正在做的工作】  
                    break ;
                }
            time++ ;
            } // while
        }

        if ( q.IsEmpty() && working.empty() && count == size -1) // 如果佇列是空的 && 工作列也是空的 && 工作列到底了 
            isEnd = true ; // 代表全部工作都完成了 
            
    }

    count = 0 ;
    int abortSize = abortList.size() ;
    newFile <<  "        [Abort Jobs]" << endl ;
    newFile <<  "        OID \tAbort\tDelay" << endl ;
    while ( count < abortSize) {
        newFile <<  "[" << count + 1 << "]\t"<< abortList.at(count).ID << "\t"<< abortList.at(count).abort << "\t" << abortList.at(count).deley<< endl ;
        count ++ ;
    } // 輸出【取消清單】

    count = 0 ;
    int doneSize = doneList.size() ;
    newFile <<  "       [Jobs Done]" << endl ;
    newFile <<  "        OID \tDeparture\tDelay" << endl ;
    while ( count < doneSize) {
        newFile <<  "[" << count + 1 << "]\t"<< doneList.at(count).ID << "\t"<< doneList.at(count).departure << "\t" << doneList.at(count).deley<< endl ;
        count ++ ;
    } // 輸出【完成清單】

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
		case 0 : break ; //跳出，結束

  		case 1 : // 以指定方法令建排序檔 
            m.readTheFile() ; // 讀檔 
            m.shellSort() ; // 希爾排序 
            m.writeTheFile() ; // 輸檔 
            cout << endl ;
            cout << "Reading Data: " << readDuration << " sec" << endl ; // 輸出讀檔時間 
            cout << "Sorting Data: " << sortDuration << " sec" << endl ; // 輸出希爾排序時間 
            cout << "Writing Data: " << writeDuration << " sec" << endl ; // 輸出輸檔時間 
            break ;
  		case 2 : // 單一CPU的佇列模擬 
            m.readTheSortedFile() ; // 讀排序好的檔 
            m.missionTwo() ; //  開始佇列模擬 
  			break ;

  		default :
			cout << endl << "command does not exist !!" << endl ;
  			break ;

	} // end switch

  } while ( command != 0 ) ;

  system( "pause") ; // pause the display
  return 0 ;
}
