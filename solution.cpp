#include<iostream>
#include<vector>
#include<cstring>
#include<string>
using namespace std;
struct Journal
{
    string name;
    int impact_factor[2];
    vector<int> indices;
    vector<int> citations;
    double ifactor;
};
class AcademicJournal{
    public:
        void Swap(Journal** a,Journal** b)
        {
            Journal* temp;
            temp=*a;
            *a=*b;
            *b=temp;
        }
        vector <string> rankByImpact(vector <string> papers)
        {
            vector<Journal*> journals;
            for(auto a=0;a<papers.size();++a)
            {
                int i;
                Journal* j_obj=new Journal;
                j_obj->name=papers[a].substr(0,papers[a].find("."));
                j_obj->impact_factor[0]=0;
                j_obj->impact_factor[1]=1;
                j_obj->indices.push_back(a);
                for(i=0;i<journals.size();++i)
                {
                    if(j_obj->name==journals[i]->name)
                    {
                        ++journals[i]->impact_factor[1];
                        journals[i]->indices.push_back(a);
                        delete j_obj;
                        break;
                    }
                }
                if(i==journals.size())
                {
                    journals.push_back(j_obj);
                }
                string citation;
                citation=papers[a].substr(papers[a].find(".")+1,papers[a].size());
                if(citation.size()>0)
                    citation.erase(citation.begin());
                string temp;
                for(auto a=0;a<citation.size();++a)
                {
                    if(citation[a]!=' ')
                    {
                        temp.push_back(citation[a]);
                    }
                    else
                    {
                        journals[i]->citations.push_back(stoi(temp));
                        temp.clear();
                    }
                }
                if(temp.size()>0)
                {
                    journals[i]->citations.push_back(stoi(temp));
                    temp.clear();
                }
            }
            for(auto i=0;i<journals.size();++i)
            {
                for(auto j=0;j<journals[i]->indices.size();++j)
                {
                    for(auto k=0;k<journals.size();++k)
                    {
                        if(k==i)
                            continue;
                        for(auto l=0;l<journals[k]->citations.size();++l)
                        {
                            if(journals[i]->indices[j]==journals[k]->citations[l])
                            {
                                ++journals[i]->impact_factor[0];
                            }
                        }
                    }
                }
            }
            for(auto i=0;i<journals.size();++i)
            {
                journals[i]->ifactor=double(journals[i]->impact_factor[0])/double(journals[i]->impact_factor[1]);
            }
            bool swapped;
            do{
                swapped=false;
                for(auto i=1;i<journals.size();++i)
                {
                    if(journals[i-1]->ifactor < journals[i]->ifactor)
                    {
                        Swap(&journals[i-1],&journals[i]);
                        swapped=true;
                    }
                    else if(journals[i-1]->ifactor == journals[i]->ifactor)
                    {
                        if(journals[i-1]->impact_factor[1] < journals[i]->impact_factor[1])
                        {
                            Swap(&journals[i-1],&journals[i]);
                            swapped=true;
                        }
						else if(journals[i-1]->impact_factor[1] == journals[i]->impact_factor[1])
                        {
                            if(journals[i-1]->name > journals[i]->name)
                            {
                                Swap(&journals[i-1],&journals[i]);
                                swapped=true;
                            }
                        }
                    }
                }
            }while(swapped);
            vector<string> result;
            for(auto i=0;i<journals.size();++i)
            {
                result.push_back(journals[i]->name);
            }
            for(auto i=0;i<journals.size();++i)
            {
                delete journals[i];
            }
            return result;
        }
};