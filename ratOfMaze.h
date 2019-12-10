//
// Created by william  on 12/9/19.
//

#ifndef TEXASHOLDEM_RATOFMAZE_H
#define TEXASHOLDEM_RATOFMAZE_H
#include <iostream>
#include <queue>
using namespace std;
class ratOfMaze{

public:
    struct Point{
        //行与列
        int row;
        int col;

        //默认构造函数
        Point(){
            row=col=-1;
        }

        Point(int x,int y){
            this->row=x;
            this->col=y;
        }

        bool operator==(const Point& rhs) const{
            if(this->row==rhs.row&&this->col==rhs.col)
                return true;
            return false;
        }
    };



    void mazePath(void* maze,int m,int n, Point& startP, Point endP,vector<Point>& shortestPath){
        int** maze2d=new int*[m];
        for(int i=0;i<m;++i){
            maze2d[i]=(int*)maze+i*n;
        }

        if(maze2d[startP.row][startP.col]==1||maze2d[startP.row][startP.col]==1) return ; //输入错误

        if(startP==endP){ //起点即终点
            shortestPath.push_back(startP);
            return;
        }

        //mark标记每一个节点的前驱节点，如果没有则为（-1，-1），如果有，则表示已经被访问
        Point** mark=new Point*[m];
        for(int i=0;i<m;++i){
            mark[i]=new Point[n];
        }

        queue<Point> queuePoint;
        queuePoint.push(startP);
        //将起点的前驱节点设置为自己
        mark[startP.row][startP.col]=startP;

        while(queuePoint.empty()==false){
            Point pointFront=queuePoint.front();
            queuePoint.pop();

            if(pointFront.row-1>=0 && maze2d[pointFront.row-1][pointFront.col]==0){//上节点连通
                if(mark[pointFront.row-1][pointFront.col]==Point()){//上节点未被访问，满足条件，如队列
                    mark[pointFront.row-1][pointFront.col]=pointFront;
                    queuePoint.push(Point(pointFront.row-1,pointFront.col)); //入栈
                    if(Point(pointFront.row-1,pointFront.col)==endP){ //找到终点
                        break;
                    }
                }
            }

            if(pointFront.col+1<n && maze2d[pointFront.row][pointFront.col+1]==0){//右节点连通
                if(mark[pointFront.row][pointFront.col+1]==Point()){//右节点未被访问，满足条件，如队列
                    mark[pointFront.row][pointFront.col+1]=pointFront;
                    queuePoint.push(Point(pointFront.row,pointFront.col+1));    //入栈
                    if(Point(pointFront.row,pointFront.col+1)==endP){ //找到终点
                        break;
                    }
                }
            }

            if(pointFront.row+1<m && maze2d[pointFront.row+1][pointFront.col]==0){//下节点连通
                if(mark[pointFront.row+1][pointFront.col]==Point()){//下节点未被访问，满足条件，如队列
                    mark[pointFront.row+1][pointFront.col]=pointFront;
                    queuePoint.push(Point(pointFront.row+1,pointFront.col));    //入栈
                    if(Point(pointFront.row+1,pointFront.col)==endP){ //找到终点
                        break;
                    }
                }
            }

            if(pointFront.col-1>=0 && maze2d[pointFront.row][pointFront.col-1]==0){//左节点连通
                if(mark[pointFront.row][pointFront.col-1]==Point()){//上节点未被访问，满足条件，如队列
                    mark[pointFront.row][pointFront.col-1]=pointFront;
                    queuePoint.push(Point(pointFront.row,pointFront.col-1));    //入栈
                    if(Point(pointFront.row,pointFront.col-1)==endP){ //找到终点
                        break;
                    }
                }
            }
        }
        if(queuePoint.empty()==false){
            int row=endP.row;
            int col=endP.col;
            shortestPath.push_back(endP);
            while(!(mark[row][col]==startP)){
                shortestPath.push_back(mark[row][col]);
                row=mark[row][col].row;
                col=mark[row][col].col;
            }
            shortestPath.push_back(startP);
        }
    }

    void ratInMaze(void* maze,int m,int n){
        Point startP(0,0);
        Point endP(m-1,n-1);
        vector<Point> vecPath;
        mazePath(maze,m,n,startP,endP,vecPath);

        if(vecPath.empty()==true)
            cout<<"no right path"<<endl;
        else{
            cout<<"shortest path:";
            for(auto i=vecPath.rbegin();i!=vecPath.rend();++i)
                printf("(%d,%d) ",i->row,i->col);
        }

    }
};
#endif //TEXASHOLDEM_RATOFMAZE_H
