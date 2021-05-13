#include<fstream>
#include<iostream>

using namespace std;

//int attended_GW[30] ,k=1;        //just for checking, which groundwork can be attended by the student (debugging)

struct Groundwork{

    int start_time , duration, end_time;
};

struct Available_Groundworks{

    int n;
    Groundwork G[30];
};

void swap_it (int  &a, int &b){                  //a function for swaping two variables. It would be used for sorting.

    int temp;
    temp = a;
    a = b;
    b = temp;
}

Available_Groundworks* initialize (int start_time[] , int duration [] , int n){                    //intializing the Available_Groundworks object

    Available_Groundworks G1;
    Available_Groundworks *ptr;
    ptr= &G1;
    G1.n = n;
    for (int i=0; i<n ; i++){
        G1.G[i].start_time = start_time[i];
        G1.G[i].duration = duration[i];
        G1.G[i].end_time = start_time[i] + duration[i];

    }
    return ptr;
}

int CalculateMaxGroundworks ( Available_Groundworks *ptr){

    int MaxGW = 2;           //the student will always be able to attend the first and the last Groundwork
    //attended_GW[0]=9;
    for (int i=1 ; i<ptr->n ; i++){

        if ( ptr->G[i].start_time >= ptr->G[i-1].end_time  &&  ptr->G[i].start_time != ptr->G[i-1].start_time){        //if the start time of next GW is more than the end time of previous GW then it can be attended
            MaxGW++;
            //attended_GW[k++] = ptr->G[i-1].start_time;
        }
    }
    //attended_GW[k++]=22;
    return MaxGW;
}

int main(){

    int start_time[30] , duration[30];
    char name[4],ch;
	ifstream fin;                    //bookmark
	fin.open( "Schedule.txt");       //adding bookmark "fin" to the readable file
	if (!fin)
        cout<<"error";               //checking if the file have contents or not

    else{
        int i=0;
        fin.seekg(0);                //attaching bookmark to the starting of the file
        while (!fin.eof()){          //bookmark will read the file till it reaches "end of file"

            fin>>name;
            fin.get(ch);
            fin>>start_time[i];
            fin.get(ch);
            fin>>duration[i];
            fin.get(ch);
            i++;
        }

        //sorting the "start_time" array

        for (int j=0; j<i ;j++){
            for (int k=j+1 ; k<i ;k++){
                if(start_time[j] > start_time[k]){
                    swap_it (start_time[j], start_time[k]);
                    swap_it (duration[j] , duration[k]);
                }
                else  if (start_time[j] == start_time[k] )                    //if the start_time is equal then sort as per duration
                        if(duration[j] < duration [k]){
                            swap_it (start_time[j], start_time[k]);
                            swap_it (duration[j] , duration[k]);
                        }
            }
        }

        /*for(int j=0;j<i;j++)
            cout<<start_time[j]<<"\t"<<duration[j]<<endl;*/                  //just for debugging purpose
        Available_Groundworks* G = initialize(start_time +1 , duration +1 ,i);
        cout<<CalculateMaxGroundworks( G );
        cout<<endl;
        //for(int i=0 ;i<k;i++)
            //cout<<attended_GW[i]<<endl;
    }

    return 0;

}
