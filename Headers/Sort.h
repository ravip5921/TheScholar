#include<fstream>

const int ORIG_FILE = 0;
const int CPY_FILE = 1;
const char AUX_SORT_FILE[] = "./sorting.txt";


void getString(std::fstream& pf, std::string& str, const int MAX_STRSIZE, char delim = ' ')
{
    char r;
    str = "";
    for(int i=0; i<MAX_STRSIZE; i++)
    {
        r = pf.get();
        if(r == delim)
            break;
        str.push_back(r);
    }
}
void putString(std::fstream& pf, std::string& str, const int MAX_STRSIZE, char delim = ' ')
{
    for(int i=0; i<MAX_STRSIZE; i++)
    {
        if(i<str.size())
            pf.put(str[i]);
        else
            pf.put(delim);
    }
}

void mergeSort(std::fstream& orig,const int noOfEls, const int ELSIZE, const char DELIM = ' ')
{
    int basepos = orig.tellg();
    //std::cout<<"\nbasepos: "<<basepos;
    std::fstream aux(AUX_SORT_FILE,std::ios_base::out);
    aux.close();
    aux.open(AUX_SORT_FILE,std::ios_base::out | std::ios_base::in);
    std::string str1, str2;
    int i,j,k,l1,l2,u1,u2,sort_size, file1;
    sort_size =1;
    file1 = ORIG_FILE; //previous sorted file is original file
    while(sort_size < noOfEls) //currently sorting size is less than no of elements
    {
        l1=0;
        k=0;

        while(l1 + sort_size < noOfEls)
        {
            l2 = l1 + sort_size;
            u1 = l2 -1;
            u2 = (l2+sort_size-1 < noOfEls)? l2+sort_size-1: noOfEls-1;

            for(i=l1,j=l2; i<=u1 && j<=u2; k++)
            {
                //READING FROM FILE
                if(file1 == ORIG_FILE)
                {
                    orig.seekg(basepos+i*ELSIZE);
                    getString(orig,str1,ELSIZE, DELIM);
                    orig.seekg(basepos+j*ELSIZE);
                    getString(orig,str2,ELSIZE, DELIM);
                }
                else
                {
                    aux.seekg(i*ELSIZE);
                    getString(aux,str1,ELSIZE, DELIM);
                    aux.seekg(j*ELSIZE);
                    getString(aux,str2,ELSIZE, DELIM);
                }
                //std::cout<<"\nread str1: "<<str1;
                //std::cout<<"\nread str2: "<<str2;
                //WRITING TO FILE
                if(str1<= str2)
                {
                    //aux[k] = x[i++];
                    //std::cout<<"\nstr1<=str2";
                    if(file1 == ORIG_FILE)
                    {
                        aux.seekp(k*ELSIZE);
                        putString(aux, str1, ELSIZE, DELIM);
                    }
                    else
                    {
                        orig.seekp(basepos+k*ELSIZE);
                        putString(orig, str1, ELSIZE, DELIM);
                    }
                    i++;
                }
                else
                {
                    //aux[k] = x[j++];
                    //std::cout<<"\nstr1>str2";
                    if(file1 == ORIG_FILE)
                    {
                        aux.seekp(k*ELSIZE);
                        putString(aux, str2, ELSIZE, DELIM);
                    }
                    else
                    {
                        orig.seekp(basepos+k*ELSIZE);
                        putString(orig, str2, ELSIZE, DELIM);
                    }
                    j++;
                }
            }

            for(; i<=u1; k++, i++)
            {
                //aux[k] = X[i++];
                if(file1 == ORIG_FILE)
                {
                    orig.seekg(basepos+i*ELSIZE);
                    getString(orig,str1,ELSIZE, DELIM);

                    aux.seekp(k*ELSIZE);
                    putString(aux, str1, ELSIZE, DELIM);
                }
                else
                {
                    aux.seekg(i*ELSIZE);
                    getString(aux,str1,ELSIZE, DELIM);

                    orig.seekp(basepos+k*ELSIZE);
                    putString(orig, str1, ELSIZE, DELIM);
                }
            }
            for(; j<=u2; k++, j++)
            {
                //aux[k] = x[j++];
                if(file1 == ORIG_FILE)
                {
                    orig.seekg(basepos+j*ELSIZE);
                    getString(orig,str1,ELSIZE, DELIM);

                    aux.seekp(k*ELSIZE);
                    putString(aux, str1, ELSIZE, DELIM);
                }
                else
                {
                    aux.seekg(j*ELSIZE);
                    getString(aux,str1,ELSIZE, DELIM);

                    orig.seekp(basepos+k*ELSIZE);
                    putString(orig, str1, ELSIZE, DELIM);
                }
            }
            l1 = u2 + 1;
        }
        for(i=l1;k<noOfEls; i++, k++)
        {
            //aux[k++] = x[i];
            if(file1 == ORIG_FILE)
                {
                    orig.seekg(basepos+i*ELSIZE);
                    getString(orig,str1,ELSIZE, DELIM);

                    aux.seekp(k*ELSIZE);
                    putString(aux, str1, ELSIZE, DELIM);
                }
                else
                {
                    aux.seekg(i*ELSIZE);
                    getString(aux,str1,ELSIZE, DELIM);

                    orig.seekp(basepos+k*ELSIZE);
                    putString(orig, str1, ELSIZE, DELIM);
                }
        }
        file1 == ORIG_FILE ? file1=CPY_FILE: file1=ORIG_FILE;
        sort_size*=2;
    }

    if(file1 == CPY_FILE)
    {
        aux.seekg(0, std::ios::end);
        int size = aux.tellg();
        aux.seekg(0);
        orig.seekp(basepos);
        char* buffer = new char[size];

        aux.read(buffer, size);
        orig.write(buffer, size);
        delete[] buffer;
    }
    aux.close();
    orig.seekp(basepos);
    remove(AUX_SORT_FILE);
}

void quickSort(std::fstream& orig,const int noOfEls, const int ELSIZE, const char DELIM = ' ')
{

}

void insertInSortedFile(std::fstream& sfile, const std::string &insert_String, const int noOfEls, const int ELSIZE, const char DELIM = ' ')
{
    int basepos = sfile.tellg();
    std::string readStr;
    int i;
    for(i=0; i<noOfEls; i++)
    {
        sfile.seekg(basepos + i*ELSIZE);
        getString(sfile, readStr, ELSIZE);
        if(insert_String == readStr)
            return;
        else if(insert_String < readStr)
            break;
    }
    if(i == noOfEls)
    {
        readStr = insert_String;
        sfile.seekg(basepos + i*ELSIZE);
        putString(sfile, readStr, ELSIZE);
    }
    else
    {
        for(int j=noOfEls; j>i; j--)
        {
            sfile.seekg(basepos + (j-1)*ELSIZE);
            getString(sfile, readStr, ELSIZE);
            sfile.seekp(basepos + j*ELSIZE);
            putString(sfile, readStr, ELSIZE);
        }
        readStr = insert_String;
        sfile.seekp(basepos + i*ELSIZE);
        putString(sfile, readStr, ELSIZE);
    }

}
