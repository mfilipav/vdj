#include "bitx.h"

using namespace std;


unsigned short getNucleotide(char ch){
    
    switch(ch) {
        case 'a':
        case 'A': return A;
        case 't':
        case 'T': return T;
        case 'c':
        case 'C': return C;
        case 'g': 
        case 'G': return G;
        default:  return 5;
    }
}

inline void runCombs( map<unsigned long, int>* hm, unsigned long xx, unsigned long mask, int ii ){

if(!((0x3B2D7 & mask)) && (ii >  18)) { insertBump(hm, ((0x38000 & xx) >> 6) | ((0x3000 & xx) >> 5) | ((0x200 & xx) >> 3) | ((0xc0 & xx) >> 2) | ((0x10 & xx) >> 1) | ((0x7 & xx) >> 0)); }
if(!((0x3C44D7 & mask)) && (ii >  22)) { insertBump(hm, ((0x3c0000 & xx) >> 10) | ((0x4000 & xx) >> 7) | ((0x400 & xx) >> 4) | ((0xc0 & xx) >> 2) | ((0x10 & xx) >> 1) | ((0x7 & xx) >> 0)); }
if(!((0xFFF & mask)) && (ii >  12)) { insertBump(hm, ((0xfff & xx) >> 0)); }
if(!((0x1A18AF & mask)) && (ii >  21)) { insertBump(hm, ((0x180000 & xx) >> 10) | ((0x20000 & xx) >> 9) | ((0x1800 & xx) >> 5) | ((0x80 & xx) >> 2) | ((0x20 & xx) >> 1) | ((0xf & xx) >> 0)); }
if(!((0x7747 & mask)) && (ii >  15)) { insertBump(hm, ((0x7000 & xx) >> 5) | ((0x700 & xx) >> 4) | ((0x40 & xx) >> 3) | ((0x7 & xx) >> 0)); }

    return;
}

inline void insertBump(map<unsigned long, int>* mp, unsigned long key){

    std::map<unsigned long, int>::iterator itr = mp->lower_bound(key);

    // Are we in the right place?
    if( (*itr).first == key ){
        (*itr).second += 1; // bump the count if we are
    } else {
        // otherwise add it to the set
        mp->insert(itr, pair<unsigned long, int>(key, 1));
    }
    return;
}


std::map<unsigned long, int>* loadSequence(char* seq){
    int len = strlen(seq);
    std::map<unsigned long, int>* res = new std::map<unsigned long, int>();
    unsigned long acc = 0;
    unsigned long nmask = 0;
    unsigned short nuc;
    
    int ii;
    for( ii = 0; ii < len; ++ii) {
        nuc = getNucleotide(seq[ii]);
        acc <<= 2;
        acc += nuc % 5;
        
        nmask <<= 2;
        if( nuc > G ){
            nmask += 3;
        }

        runCombs(res, acc, nmask, ii);    
    }
    
    return res;
}

/*
std::list<std::set<unsigned long>* > makeSignatures( std::list<std::set<unsigned long>* > subunits ){

  std::list<std::set<unsigned long>* > res;

  std::list<std::set<unsigned long>* >::iterator prmItr = subunits.begin();
  std::list<std::set<unsigned long>* >::iterator secItr = subunits.begin();

  //TODO double check the number of copies I'm making. Are they all necessary?
  while( prmItr != subunits.end() ) {
        
      set<unsigned long>* tset = new std::set<unsigned long>((*prmItr)->begin(), (*prmItr)->end());
      set<unsigned long>* swap = new std::set<unsigned long>();
      set<unsigned long>::iterator itr = tset->begin();
      while( secItr != subunits.end() ){
        if( (*secItr) != (*prmItr) ){
          set_difference(
                tset->begin(), tset->end(), 
                (*secItr)->begin(), (*secItr)->end(), inserter(*swap, swap->begin()));
        }
        delete tset;
        tset = swap;
        swap = new std::set<unsigned long>();
        
        res.push_back(tset);
      }
  }

  return res;
}

std::set<unsigned int>* matchAll( std::list<unsigned int>* input, std::list<std::set<unsigned long>* > signatures ){

    std::set<unsigned int>* result = new std::set<unsigned int>();

    if( input->empty() ) { return result; }
    
    unsigned int buffer = input->front();
    input->pop_front();

    do {


    } while( !input->empty() );

    return result;

}

*/


int main(int argc, char** argv){
    
    char* seq = "CGATATGCACGCTCTCGACGCGCGACGCACGACGACACACGAGAGNGNGNGACGACGACGGACGACGA";
    std::map<unsigned long, int>* f = loadSequence(seq);

    std::map<unsigned long, int>::iterator itr;

    for( itr = f->begin(); itr != f->end() ; itr++){
        printf("0x%X: %d\n", (unsigned int) (*itr).first, (*itr).second);
    }

    delete f;
    return 0;

}
