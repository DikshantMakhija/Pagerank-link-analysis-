
#include <iostream>
//#include <algorithm>
using namespace std;


struct Node{
    int val;
    Node *down,*next;
    int i,j;
};

void AddLink(Node* head,int j,int i){
    Node *tri,*trj,*headi,*headj;
    // tri and trj are pointers to traverse where, i for row and j for column
    tri = head;
    trj = head;
    headi = new Node();
    headj = new Node();
    Node* link = new Node();
    Node *tmp;
    int z=0,k=0;
        while(tri->down!=head){     // traversing down for row
            if(tri->down->i>i)      break;
            tri = tri->down;
            if(tri->i==i){
                z = 1;
                break;
            }
        }
       while(trj->next!=head){      // traversing right for column
          if(trj->next->j>j)      break;
          trj = trj->next;
          if(trj->j==j){
                if(z==1)
                {
                    z = 4;
                }
                else{
                    z = 2;
                }
                break;
            }
        }

    switch(z){
        case 0:             // if i and j both are non existing
            link->i = i;
            link->j = j;
            link->val = 1;
            headi->i = i;       // header for i
            headj->j = j;       // header for j
            headi->j = -1;
            headj->i = -1;
            headi->val = -1;
            headj->val = -1;
            headj->next = trj->next;
            trj->next = headj;
            headi->down = tri->down;
            tri->down = headi;
            headi->next = link;
            link->next = headi;
            headj->down = link;
            link->down = headj;
            break;
        case 1:                 // if i header already exists but j doesnot
            link->i = i;
            link->j = j;
            link->val = 1;
            headj->j = j;
            headj->i = -1;
            headj->val = -1;
            headj->next = trj->next;
            trj->next = headj;
            headj->down = link;
            link->down = headj;
            tmp = tri;
            while(tmp->next!=tri){
                if(tmp->next->j>j)      break;
                tmp = tmp->next;
            }
            link->next = tmp->next;
            tmp->next = link;
            break;
        case 2:                 // if i header already exists but j doesnot
            link->i = i;
            link->j = j;
            link->val = 1;
            headi->i = i;
            headi->j = -1;
            headi->val = -1;
            headi->down = tri->down;
            tri->down = headi;
            headi->next = link;
            link->next = headi;
            tmp = trj;
            while(tmp->down!=trj){
                if(tmp->down->i>i)      break;
                tmp = tmp->down;
            }
            link->down = tmp->down;
            tmp->down = link;
            break;
        case 4:                     // if i and j both headers already exist
            tmp = trj;              // if i and j headers exist but link i,j doesnot
            while(tmp->down!=trj){
                if(tmp->down->i>i)     break;
                tmp = tmp->down;
                if(tmp->i==i){
                    z = 3;
                    break;
                }
            }
            if(z==3)
            {                       // if link i,j exist already
                tmp->val = tmp->val + 1;
                break;
            }
            else{
                Node *tmp1;
                tmp1 = tri;
                while(tmp1->next!=tri){
                    if(tmp1->next->j>j)   break;
                    tmp1 = tmp1->next;
                }
                link->i = i;
                link->j = j;
                link->val = 1;
                link->next = tmp1->next;
                tmp1->next = link;
                link->down = tmp->down;
                tmp->down = link;
                break;
            }
    }
}

void DeleteLink(Node* head,int j,int i){
    Node *tri,*trj,*previ,*prevj,*tmpj,*tmpi;
    tri = head;
    int z=0;
    while(tri->down!=head){            // tri and trj same as above
        tri = tri->down;
        if(tri->i==i){      // traversing in i
            z=1;
            break;
        }
        if(tri->down->i>i)      break;
    }
    trj = head;
    if(z==1){               // if i exists traversing in j
        while(trj->next!=head){
        if(trj->next->j>j)      break;
            trj = trj->next;
            if(trj->j==j){
                z=2;
                break;
            }
        }
    }
    if(z==2){               // if both exits further traversing along the row i
        tmpj = tri;
        while(tmpj->next!=tri){
            prevj = tmpj;
            tmpj = tmpj->next;
            if(tmpj->j==j){
                tmpj->val = tmpj->val - 1;
                if(tmpj->val==0){       // if node becomes NULL or links become zero, removing node link from j direction
                    prevj->next = tmpj->next;
                    z = 3;
                }
                break;
            }
        }
        if(z==3){                       // if node is null further removing node link from i direction
        tmpi = trj;
        while(tmpi->down!=trj){
            previ = tmpi;
            tmpi = tmpi->down;
            if(tmpi->i==i){
                previ->down = tmpi->down;
                free(tmpi);
                //free(tmpj);
                break;
            }
        }
        }
    }
}

int RetrieveValue(Node* head,int j,int i){
    Node *tri,*tmp;
    tri = head;
    int z=0;

    while(tri->down!=head){         // traversing down for row
        if(tri->down->i>i)  break;  // if immediately next head has higher value than i
        tri = tri->down;
        if(tri->i==i){
            tmp = tri;
            while(tmp->next!=tri){      // traversing right for column
                if(tmp->next->j>j)      break;  // if immediately next head has higher value than j
                tmp = tmp->next;
                if(tmp->j==j)   return tmp->val;
            }
        }
    }
    return 0;
}


int RetrieveRowSumUptoKthColumn(Node* head,int i,int k){
    int sum=0;
    Node *tri,*tmp;
    tri = head;

    while(tri->down!=head){     // traversing down for row
        if(tri->down->i>i)    break;
        tri = tri->down;
        if(tri->i==i){
            tmp = tri;
            sum=0;
            while(tmp->next->j<k && tmp->next!=tri){    // traversing right till Kth column
                tmp = tmp->next;
                if(tmp->j>=0)        sum = sum + tmp->val;
            }
            break;
        }
    }
    return sum;
}

int RetrieveColumnSumUptoKthRow(Node* head,int j,int k){
    int sum=0;
    Node *trj,*tmp;
    trj = head;

    while(trj->next!=head){     // traversing right for column
        if(trj->next->j>j)    break;
        trj = trj->next;
        if(trj->j==j){
            tmp = trj;
            while(tmp->down->i<k && tmp->down!=trj){    // traversing down till Kth column
                tmp = tmp->down;
                if(tmp->i>=0)       sum = sum + tmp->val;
            }
            break;
        }
    }

    return sum;
}

void MultiplyVector(Node* head,int n,long *a){
    if(n==0)    cout<<n;                // if no of elements in verctor is zero
    else if(head==NULL){                // if all entries of matrix are zero
        for(int l=0;l<n;l++)       cout<<0<<" ";
        }
    else
    {                                   // if above 2 conditions are none existing
        Node *tri,*tmp;
        long mult[n]={0};
        //for(int l=0;l<n;l++)       mult[l] = 0;
        tri = head;
        while(tri->down!=head && tri->down->i<n && tri->down->i>=0){        // for elements from i=0 to n-1 and
            tri = tri->down;
            tmp = tri;
            while(tmp->next!=tri && tmp->next->j<n && tmp->next->j>=0){
                tmp = tmp->next;
                mult[tri->i] += (tmp->val)*a[tmp->j];
            }
        }
        for(int l=0;l<n;l++)       cout<<mult[l]<<" ";
    }
    cout<<"\n";
}


int main(){
    int q,n;
    Node *head;
    head = new Node();
    head->i = -1;
    head->j = -1;
    head->val = -1;
    head->next = head;
    head->down = head;
    cin>>q;
    for(int l=0;l<q;l++){       // loop for no of operations
        int i,j,val,m;
        long *a;
        cin>>n;
        if(n<6)     cin >> i >> j;
        if(n==6){
                cin>>m;
                a = new long[m];
                for(int h=0;h<m;h++)        cin>>a[h];      // inputing values for multiply-vector
        }
        switch(n){
            case 1:
                AddLink(head,i,j);
                break;
            case 2:
                DeleteLink(head,i,j);
                break;
            case 3:
                val = RetrieveValue(head,i,j);
                cout<<val<<"\n";
                break;
            case 4:
                val = RetrieveRowSumUptoKthColumn(head,i,j);
                cout<<val<<"\n";
                break;
            case 5:
                val = RetrieveColumnSumUptoKthRow(head,i,j);
                cout<<val<<"\n";
                break;
            case 6:
                MultiplyVector(head,m,a);
                break;
        }
    }
    return 0;
}
