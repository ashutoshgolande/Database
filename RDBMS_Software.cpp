#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#include <algorithm>
#include <cassert>
#include <tuple>
#include <string>

using namespace std;

class Attr
{ // Base class for attributes
public:
    virtual bool operator==(const Attr &right) = 0;
    virtual bool operator!=(const Attr &right) = 0;
    virtual bool operator<(const Attr &right) = 0;
    virtual bool operator<=(const Attr &right) = 0;
    virtual bool operator>(const Attr &right) = 0;
    virtual bool operator>=(const Attr &right) = 0;
    virtual Attr *clone() const = 0;
    virtual ~Attr() {}
};

class IntAttr : public Attr
{
private:
    int value;

public:
    IntAttr(int val) : value(val) {}
    bool operator==(const Attr &right) override
    {
        return value == dynamic_cast<const IntAttr &>(right).value;
    }
    bool operator!=(const Attr &right) override
    {
        return value != dynamic_cast<const IntAttr &>(right).value;
    }
    bool operator<(const Attr &right) override
    {
        return value < dynamic_cast<const IntAttr &>(right).value;
    }
    bool operator<=(const Attr &right) override
    {
        return value <= dynamic_cast<const IntAttr &>(right).value;
    }
    bool operator>(const Attr &right) override
    {
        return value > dynamic_cast<const IntAttr &>(right).value;
    }
    bool operator>=(const Attr &right) override
    {
        return value >= dynamic_cast<const IntAttr &>(right).value;
    }
    Attr *clone() const override
    {
        return new IntAttr(value);
    }
    int get()
    {
        return value;
    }
};

class FloatAttr : public Attr
{
private:
    float value;

public:
    FloatAttr(float val) : value(val) {}
    bool operator==(const Attr &right) override
    {
        return value == dynamic_cast<const FloatAttr &>(right).value;
    }
    bool operator!=(const Attr &right) override
    {
        return value != dynamic_cast<const FloatAttr &>(right).value;
    }
    bool operator<(const Attr &right) override
    {
        return value < dynamic_cast<const FloatAttr &>(right).value;
    }
    bool operator<=(const Attr &right) override
    {
        return value <= dynamic_cast<const FloatAttr &>(right).value;
    }
    bool operator>(const Attr &right) override
    {
        return value > dynamic_cast<const FloatAttr &>(right).value;
    }
    bool operator>=(const Attr &right) override
    {
        return value >= dynamic_cast<const FloatAttr &>(right).value;
    }
    Attr *clone() const override
    {
        return new FloatAttr(value);
    }
    float get()
    {
        return value;
    }
};

class StringAttr : public Attr
{
private:
    string value;

public:
    StringAttr(string val) : value(val) {}
    bool operator==(const Attr &right) override
    {
        return value == dynamic_cast<const StringAttr &>(right).value;
    }
    bool operator!=(const Attr &right) override
    {
        return value != dynamic_cast<const StringAttr &>(right).value;
    }
    bool operator<(const Attr &right) override
    {
        return value < dynamic_cast<const StringAttr &>(right).value;
    }
    bool operator<=(const Attr &right) override
    {
        return value <= dynamic_cast<const StringAttr &>(right).value;
    }
    bool operator>(const Attr &right) override
    {
        return value > dynamic_cast<const StringAttr &>(right).value;
    }
    bool operator>=(const Attr &right) override
    {
        return value >= dynamic_cast<const StringAttr &>(right).value;
    }
    Attr *clone() const override
    {
        return new StringAttr(value);
    }
    string get()
    {
        return value;
    }
};
class Record
{ // Class for records
public:
    vector<Attr *> attrs;

public:
    Record(vector<Attr *> a) : attrs(a) {}
    ~Record()
    {
        for (auto a : attrs)
        {
            delete a;
        }
    }

};
class Relation
{
public:
    int nattr, nrecs;         // number of attributes and records
    vector<string> attrnames; // schema
    vector<int> attrinds;     // mapping schema to indices
    list<Record *> recs;      // list of records
    Relation(list<Record *> recs, int nattr, int nrecs, vector<string> attrnames, vector<int> attrinds) : recs(recs), nattr(nattr), nrecs(nrecs), attrnames(attrnames), attrinds(attrinds)
    {
    }
    void display()
    {
        for (int i = 0; i < attrnames.size(); i++)
        {
            cout << attrnames[i] << "\t\t\t\t";
        }
        cout << "\n";
        list<Record *>::iterator it;
        for (it = recs.begin(); it != recs.end(); it++)
        {
            Record *x = *it;
            vector<Attr *> o = x->attrs;
            for (int i = 0; i < nattr; i++)
            {
                IntAttr *m;
                StringAttr *y;
                FloatAttr *z;
                switch (attrinds[i])
                {
                case 1:
                    m = static_cast<IntAttr *>(o[i]);
                    cout << m->get() << "\t\t\t\t";
                    break;
                case 2:

                    y = static_cast<StringAttr *>(o[i]);
                    cout << y->get() << "\t\t\t\t";
                    break;

                case 3:
                    z = static_cast<FloatAttr *>(o[i]);
                    cout << z->get() << "\t\t\t\t";
                    break;
                }
            }

            cout << "\n";
        }
    }
};
enum datatype
{
    Int = 1,
    String,
    Float
};
typedef struct DNFformula
{
    list<list<tuple<string, char, Attr *>>> ops;
} DNFformula;
bool isSame(Record *x, Record *y)
{
    vector<Attr *> xvec;
    vector<Attr *> yvec;
    xvec = x->attrs;
    yvec = y->attrs;
    int size = xvec.size();
    int count = 0;
    for (int i = 0; i < size; i++)
    {
        if (*xvec[i] == *yvec[i])
        {
            count++;
        }
    }
    if (count == size)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool isPresent(list<Record *> &recs, Record *r)
{
    if (recs.empty())
    {
        return false;
    }
    else
    {
        list<Record *>::iterator it;
        for (it = recs.begin(); it != recs.end(); it++)
        {
            Record *x = *it;
            if (isSame(x, r))
            {
                return true;
            }
        }
        return false;
    }
}
void addRecord(list<Record *> &l, Record *r)
{
    if (!isPresent(l, r))
    {
        l.push_back(r);
    }
}
Record *sameRecord(list<Record *> &l, Record *r)
{
    if (isPresent(l, r))
    {
        list<Record *>::iterator it;
        for (it = l.begin(); it != l.end(); it++)
        {
            Record *x = *it;
            if (isSame(x, r))
            {
                return x;
            }
        }
    }
    else
    {
        return NULL;
    }
    return NULL;
}
void deleteRecord(list<Record *> &l, Record *r)
{
    Record *r1 = sameRecord(l, r);
    if (r1 != NULL)
    {
        l.remove(r1);
    }
}
Relation *makeRelation()
{
    int nattr, nrecs;         // number of attributes and records
    vector<string> attrnames; // schema
    vector<int> attrinds;     // mapping schema to indices
    list<Record *> recs;
    // list of records
    cout << "plz enter how many attributes you have\n";
    cin >> nattr;
    for (int i = 0; i < nattr; i++)
    {
        int d;
        cout << "plz select the attribute " << i + 1 << " datatype\n\n\n";
        cout << "1 ----> int\n2 ----> string\n3 ----> float\n\n";
        cin >> d;
        attrinds.push_back(d);
    }
    cout << "plz enter the attributes name\n";
    for (int i = 0; i < nattr; i++)
    {
        string s;
        cout << "enter the attribute " << i + 1 << " name\n";
        fflush(stdin);
        getline(cin, s);
        attrnames.push_back(s);
    }
    cout << "plz enter how many records you have\n";
    cin >> nrecs;
    for (int j = 0; j < nrecs; j++)
    {
        vector<Attr *> a;
        cout << "enter for the record " << j + 1 << "\n\n";
        for (int i = 0; i < nattr; i++)
        {
            cout << "enter the value of " << attrnames[i];
            string noo;
            int n;
            float n2;
            switch (attrinds[i])
            {
            case 1:

                cin >> n;
                a.push_back(new IntAttr(n));
                break;

            case 2:

                // cin >> noo;
                fflush(stdin);
                getline(cin, noo);
                a.push_back(new StringAttr(noo));
                break;
            case 3:

                cin >> n2;
                a.push_back(new FloatAttr(n2));
                break;
            }
        }
        Record *r = new Record(a);
        addRecord(recs, r);
    }
    Relation *r = new Relation(recs, nattr, nrecs, attrnames, attrinds);

    return r;
}
bool isValidForSetOperation(Relation *R1, Relation *R2)
{
    if (R1->attrinds == R2->attrinds)
    {
        return true;
    }
    else
    {
        return false;
    }
}
Relation *unions(Relation *R1, Relation *R2)
{
    Relation *unionOfRelation;
    if (isValidForSetOperation(R1, R2))
    {
        list<Record *> listOfRecord1 = R1->recs;
        list<Record *> listOfRecord2 = R2->recs;
        list<Record *> unionListOfRecords;
        int nattr = R1->nattr;
        unionListOfRecords = listOfRecord1;
        list<Record *>::iterator it;
        for (it = listOfRecord2.begin(); it != listOfRecord2.end(); it++)
        {
            Record *r = *it;
            addRecord(unionListOfRecords, r);
        }
        int nrecs = unionListOfRecords.size();
        vector<string> attrnames = R1->attrnames;
        vector<int> attrinds = R1->attrinds;
        unionOfRelation = new Relation(unionListOfRecords, nattr, nrecs, attrnames, attrinds);
        return unionOfRelation;
    }
    else
    {
        return NULL;
    }
}
Relation *difference(Relation *R1, Relation *R2)
{
    Relation *differenceOfRelation;
    if (isValidForSetOperation(R1, R2))
    {
        list<Record *> listOfRecord1 = R1->recs;
        list<Record *> listOfRecord2 = R2->recs;
        list<Record *> differenceListOfRecords;
        int nattr = R1->nattr;
        differenceListOfRecords = listOfRecord1;
        list<Record *>::iterator it;
        for (it = listOfRecord2.begin(); it != listOfRecord2.end(); it++)
        {
            Record *r = *it;
            deleteRecord(differenceListOfRecords, r);
        }
        int nrecs = differenceListOfRecords.size();
        vector<string> attrnames = R1->attrnames;
        vector<int> attrinds = R1->attrinds;
        differenceOfRelation = new Relation(differenceListOfRecords, nattr, nrecs, attrnames, attrinds);
        return differenceOfRelation;
    }
    else
    {
        return NULL;
    }
}
Relation *catersianproduct(Relation *R1, Relation *R2)
{
    if (isValidForSetOperation(R1, R2))
    {
        vector<Attr *> a;
        int nattr = R1->nattr + R2->nattr;
        vector<string> attrname1(R1->attrnames);
        vector<string> attrname2(R2->attrnames);
        vector<string> attrnames(attrname1);
        attrnames.insert(attrnames.end(), attrname2.begin(), attrname2.end());
        vector<int> attrinds1(R1->attrinds);
        vector<int> attrinds2(R2->attrinds);
        vector<int> attrinds(attrinds1);
        attrinds.insert(attrinds.end(), attrinds2.begin(), attrinds2.end());
        list<Record *> listOfRecord1 = R1->recs;
        list<Record *> listOfRecord2 = R2->recs;
        list<Record *> cartesianproductListOfRecords;
        list<Record *>::iterator it1;
        list<Record *>::iterator it2;

        for (it1 = listOfRecord1.begin(); it1 != listOfRecord1.end(); it1++)
        {
            Record *x = *it1;
            vector<Attr *> attr1(x->attrs);

            for (it2 = listOfRecord2.begin(); it2 != listOfRecord2.end(); it2++)
            {
                Record *y = *it2;
                vector<Attr *> attr2(y->attrs);
                vector<Attr *> attr(attr1);
                attr.insert(attr.end(), attr2.begin(), attr2.end());
                Record *r = new Record(attr);
                addRecord(cartesianproductListOfRecords, r);
            }
        }
        int nrecs = cartesianproductListOfRecords.size();
        Relation *cartesianproductListOfRelation = new Relation(cartesianproductListOfRecords, nattr, nrecs, attrnames, attrinds);
        return cartesianproductListOfRelation;
    }
    else
    {
        return NULL;
    }
}
Relation *projection(Relation *R1, list<string> projectattrs)
{
    vector<int> v;
    list<string>::iterator it1;
    vector<string> s = R1->attrnames;
    vector<int> a = R1->attrinds;
    vector<int> attrinds;
    list<Record *> l = R1->recs;
    list<Record *> projectionListOfRecords;
    for (it1 = projectattrs.begin(); it1 != projectattrs.end(); it1++)
    {
        string x = *it1;
        for (int i = 0; i < s.size(); i++)
        {
            if (x == s[i])
            {
                v.push_back(i);
            }
        }
    }
    int nattr = v.size();
    vector<string> attrnames;
    for (int i = 0; i < v.size(); i++)
    {
        attrinds.push_back(a[v[i]]);
        attrnames.push_back(s[v[i]]);
    }
    list<Record *>::iterator it2;
    for (it2 = l.begin(); it2 != l.end(); it2++)
    {
        Record *x = *it2;
        vector<Attr *> m = x->attrs;
        vector<Attr *> newm;
        int count = 0;
        for (int i = 0; i < m.size(); i++)
        {
            if (i == v[count])
            {

                newm.push_back(m[i]);
                count++;
            }
        }
        Record *r = new Record(newm);
        addRecord(projectionListOfRecords, r);
    }
    int nrecs = projectionListOfRecords.size();
    Relation *projectionListOfRelation = new Relation(projectionListOfRecords, nattr, nrecs, attrnames, attrinds);
    return projectionListOfRelation;
}
Relation *renames(Relation *R1, string s1, string s2)
{
    vector<string> s = R1->attrnames;
    vector<string> attrnames;
    for (int i = 0; i < s.size(); i++)
    {
        if (s1 == s[i])
        {
            attrnames.push_back(s2);
        }
        else
        {
            attrnames.push_back(s[i]);
        }
    }
    Relation *renameListOfRelation = new Relation(R1->recs, R1->nattr, R1->nrecs, attrnames, R1->attrinds);
    return renameListOfRelation;
}
Relation *intersection(Relation *R1, Relation *R2)
{
    if (isValidForSetOperation(R1, R2))
    {
        Relation *i1 = unions(R1, R2);
        Relation *i2 = difference(R1, R2);
        Relation *i3 = difference(R2, R1);
        Relation *i4 = unions(i2, i3);
        Relation *i5 = difference(i1, i4);
        return i5;
    }
    else
    {
        return NULL;
    }
}
int domainOfAttribute(string attrname, Relation *R1)
{
    vector<string> s = R1->attrnames;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == attrname)
        {
            return R1->attrinds[i];
        }
    }
    return 0;
}

bool check(Relation *R1, Record *x, string attrname, char oper, Attr *attr)
{
    int index = domainOfAttribute(attrname, R1);
    vector<Attr *> att = x->attrs;
    IntAttr *i1;
    IntAttr *i2;
    FloatAttr *f1;
    FloatAttr *f2;
    StringAttr *s1;
    StringAttr *s2;
    switch (index)
    {
    case 1:
        i1 = static_cast<IntAttr *>(attr);
        i2 = static_cast<IntAttr *>(att[index]);
        switch (oper)
        {
        case '>':
            if (*i1 > *i2)
            {
                return true;
            }
            else
            {
                return false;
            }
            break;
        case '<':
            if (*i1 < *i2)
            {
                return true;
            }
            else
            {
                return false;
            }
            break;
        case '=':
            if (*i1 == *i2)
            {
                return true;
            }
            else
            {
                return false;
            }
            break;
        case '!':
            if (*i1 != *i2)
            {
                return true;
            }
            else
            {
                return false;
            }
            break;
        }
        break;
    case 2:
        s1 = static_cast<StringAttr *>(attr);
        s2 = static_cast<StringAttr *>(att[index]);
        switch (oper)
        {
        case '>':
            if (*s1 > *s2)
            {
                return true;
            }
            else
            {
                return false;
            }
            break;
        case '<':
            if (*s1 < *s2)
            {
                return true;
            }
            else
            {
                return false;
            }
            break;
        case '=':
            if (*s1 == *s2)
            {
                return true;
            }
            else
            {
                return false;
            }
            break;
        case '!':
            if (*s1 != *s2)
            {
                return true;
            }
            else
            {
                return false;
            }
            break;
        }
        break;

    case 3:
        f1 = static_cast<FloatAttr *>(attr);
        f2 = static_cast<FloatAttr *>(att[index]);
        switch (oper)
        {
        case '>':
            if (*f1 > *f2)
            {
                return true;
            }
            else
            {
                return false;
            }
            break;
        case '<':
            if (*f1 < *f2)
            {
                return true;
            }
            else
            {
                return false;
            }
            break;
        case '=':
            if (*f1 == *f2)
            {
                return true;
            }
            else
            {
                return false;
            }
            break;
        case '!':
            if (*f1 != *f2)
            {
                return true;
            }
            else
            {
                return false;
            }
            break;
        }
        break;
    }
    return false; 
}
Relation *selection(Relation *R1, DNFformula *f)
{
    list<Record *> l = R1->recs;
    list<Record *> temp;

    Relation *answeri = R1;
    Relation *answerf = R1;
    Relation *tempR1;
    Relation *uni;
    for (auto it2 = f->ops.begin(); it2 != f->ops.end(); it2++)
    {
        for (auto it3 = (*it2).begin(); it3 != (*it2).end(); it3++)
        {
            tuple<string, char, Attr *> t = *it3;
            string attrname = get<0>(t);
            char oper = get<1>(t);
            Attr *attr = get<2>(t);
            for (auto it1 = l.begin(); it1 != l.end(); it1++)
            {
                Record *x = *it1;
                if (check(R1, x, attrname, oper, attr))
                {
                    temp.push_back(x);
                }
            }
            tempR1 = new Relation(temp, R1->nattr, temp.size(), R1->attrnames, R1->attrinds);
            answeri = intersection(tempR1, answeri);
            
        }
        answerf = unions(answeri, answerf);
    }
    return answerf;
}
void displayRelationList(vector<Relation *> Relationlist)
{
    for (int i = 0; i < Relationlist.size(); i++)
    {
        Relation *x = Relationlist[i];
        cout << i + 1 << "\n\n\n";
        x->display();
    }
}
Relation *SelectedRelation(vector<Relation *> Relationlist, int index)
{
    return Relationlist[index - 1];
}
void deleteRelation(vector<Relation *> &Relationlist, int index)
{
    vector<Relation *> temp;
    for (int i = 0; i < Relationlist.size(); i++)
    {
        if (i != index - 1)
        {
            temp.push_back(Relationlist[i]);
        }
    }
    Relationlist = temp;
}
int main()
{
    vector<Relation *> Relationlist;
    Relation *newRelation1;
    // Relation* newRelation2;
    Relation *op1;
    Relation *op2;
    Relation *ans;
    int n;

    while (1)
    {
        cout << "Which Operation do you want to perform\n\n0 ---> exit program\n1 ---> create relation\n2 ---> Union\n3 ---> Difference\n4 ---> Cartesian Product\n5 ---> Projection\n6 ---> Rename\n7 ---> display relation\n8 ---> Delete\n\n";
        cin >> n;
        switch (n)
        {
        case 0:
            break;
        case 1:
            newRelation1 = makeRelation();
            Relationlist.push_back(newRelation1);
            break;
        case 2:
            if (Relationlist.size() < 2)
            {
                cout << "you dont have enough relations\n\n";
            }
            else
            {
                int x1;
                int x2;
                cout << "Select relation 1\n";
                displayRelationList(Relationlist);
                cin >> x1;
                cout << "Relation " << x1 << " is Selected\n";
                cout << "Select relation 2\n";
                displayRelationList(Relationlist);
                cin >> x2;
                cout << "Relation " << x2 << " is Selected\n";
                op1 = SelectedRelation(Relationlist, x1);
                op2 = SelectedRelation(Relationlist, x2);
                ans = unions(op1, op2);
                if (ans != NULL)
                {
                    cout << "Union is\n\n";
                    ans->display();
                }
                else
                {
                    cout << "Union is not possible\n\n";
                }
            }
            break;
        case 3:
            if (Relationlist.size() < 2)
            {
                cout << "you dont have enough relations\n\n";
            }
            else
            {
                int x1;
                int x2;
                cout << "Select relation 1\n";
                displayRelationList(Relationlist);
                cin >> x1;
                cout << "Relation " << x1 << " is Selected\n";
                cout << "Select relation 2\n";
                displayRelationList(Relationlist);
                cin >> x2;
                cout << "Relation " << x2 << " is Selected\n";
                op1 = SelectedRelation(Relationlist, x1);
                op2 = SelectedRelation(Relationlist, x2);
                ans = difference(op1, op2);
                if (ans != NULL)
                {
                    cout << "Difference is\n\n";
                    ans->display();
                }
                else
                {
                    cout << "Difference is not possible\n\n";
                }
            }
            break;
        case 4:
            if (Relationlist.size() < 2)
            {
                cout << "you dont have enough relations\n\n";
            }
            else
            {
                int x1;
                int x2;
                cout << "Select relation 1\n";
                displayRelationList(Relationlist);
                cin >> x1;
                cout << "Relation " << x1 << " is Selected\n";
                cout << "Select relation 2\n";
                displayRelationList(Relationlist);
                cin >> x2;
                cout << "Relation " << x2 << " is Selected\n";
                op1 = SelectedRelation(Relationlist, x1);
                op2 = SelectedRelation(Relationlist, x2);
                ans = catersianproduct(op1, op2);
                if (ans != NULL)
                {
                    cout << "Cartesian Product\n\n";
                    ans->display();
                }
                else
                {
                    cout << "Cartesian Product is not possible\n\n";
                }
            }
            break;

        case 5:
            if (Relationlist.size() < 1)
            {
                cout << "you dont have enough relations\n\n";
            }
            else
            {
                int x1;
                int x2;
                string s1;
                list<string> s;
                cout << "Select relation\n";
                displayRelationList(Relationlist);
                cin >> x1;
                cout << "Relation " << x1 << " is Selected\n";
                op1 = SelectedRelation(Relationlist, x1);
                cout << "enter how many attributes you want to project\n";
                cin >> x2;
                for (int i = 0; i < x2; i++)
                {
                    cout << "enter the attribute " << i + 1 << " name";
                fflush(stdin);
                getline(cin,s1);
                    s.push_back(s1);
                }

                ans = projection(op1, s);
                cout << "New Relation after Projection is\n\n";
                ans->display();
            }
            break;

        case 6:
            if (Relationlist.size() < 1)
            {
                cout << "you dont have enough relations\n\n";
            }
            else
            {
                int x1;
                string s1;
                string s2;
                cout << "Select relation\n";
                displayRelationList(Relationlist);
                cin >> x1;
                cout << "Relation " << x1 << " is Selected\n";
                op1 = SelectedRelation(Relationlist, x1);
                cout << "enter which attribute you want to rename\n";
                fflush(stdin);
                getline(cin,s1);
                cout << "By which attribute you want to rename\n";
                fflush(stdin);
                getline(cin,s2);
                ans = renames(op1, s1, s2);
                cout << "New Relation after Rename is\n";
                ans->display();
            }
            break;
        case 7:
            if (Relationlist.size() < 1)
            {
                cout << "you dont have enough relations\n\n";
            }
            else
            {
                cout << "All Relation that you have are\n\n\n";
                displayRelationList(Relationlist);
            }
            break;
        case 8:
            if (Relationlist.size() < 1)
            {
                cout << "you dont have enough relations\n\n";
            }
            else
            {
                int x1;
                int x2;
                string s1;
                cout << "Select relation\n";
                displayRelationList(Relationlist);
                cin >> x1;
                cout << "Relation " << x1 << " is Selected\n";
                deleteRelation(Relationlist, x1);
                cout << "Deleted\n\n";
            }
        }

        if (n == 0)
        {
            break;
        }
    }

    return 0;
}
