#include "path.h"

Path::Path(vector<string> string_points): QObject() , QGraphicsPathItem()

{
    // add the textValue to the Scene
    this->textValue = new QGraphicsTextItem();
    this->textValue->setPlainText("RAY22222");
    // convert the string to points
    vector<QPointF> points = convert_strings_Points(string_points);
//    for (uint i =0 ; i< points.size() ; i++) { cout << points[i].x() << "," << points[i].y() << endl;}
    // initail the pos of the path
    QPainterPath temp_path(points[0]);
    if(points.size() > 1)
        for (uint i = 1 ; i < points.size(); i++)
            temp_path.lineTo(points[i]);

    // initail the color
    this->color = INITIAL_COLOR;
    this->pen = QPen(this->color);
    this->pen.setWidth(PATH_WIDTH);

    // create the QGraphicsPathItem from QPainterPath
    this->setPath(temp_path);
    this->setPen(this->pen);
    emit addTextItem();
}
void Path::setColor(QColor clr , int Width )
{
    this->color = clr;
    this->pen.setColor(this->color);
    this->pen.setWidth(Width);
    this->setPen(this->pen);
}

void Path::setWidth(int Width)
{
    this->pen.setWidth(Width);
    this->setPen(this->pen);
}
void Path::setTextValue(int value)
{
    QString Value = QString::number(value);
}
vector<QPointF> Path::convert_strings_Points(vector<string> points)
{
    vector<QPointF> QpointsF;
    for (uint i =0 ; i< points.size(); i++)
    {
        vector<string> point = split_string(points[i],",");
        QpointsF.push_back(QPointF(  stoi(point[0]) , stoi(point[1])  ));
    }
    return QpointsF;}
vector<string> Path :: split_string(string s,string splitter)
{
    // remove space noise
    for (int i =0 ;i<s.length();i++)
        if ( s[i] == ' ')
            s.erase(i,1);

    vector<string> splitted;
    uint n = s.length();
    int pos = 0;
    int start = pos;
    while (pos != string::npos)
    {
        pos = s.find_first_of(splitter,pos+1);
        string splitted_string = s.substr(start,pos-start);
        splitted.push_back(splitted_string);
        start = pos+1;
    }

    return splitted;}
