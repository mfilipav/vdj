#include <assert.h>
#include <signal.h>

#include <string>
#include <utility>
#include <vector>

#ifndef __BANDED_ALIGNMENT__
#define __BANDED_ALIGNMENT__

template <class T>
class MatrixCol;

template <class T>
class BandedMatrix;

template <class T>
class BandedMatrixIterator
{
    public:
        BandedMatrixIterator();
        BandedMatrixIterator(const BandedMatrixIterator<T> &itr);
        BandedMatrixIterator(std::vector<MatrixCol<T> > &itr, int size);
        ~BandedMatrixIterator();
        //FIXME these operators are broken. fix em.
        bool operator== (BandedMatrixIterator<T> &itr); 
        bool operator!= (BandedMatrixIterator<T> &itr); 
        
        bool hasNext();
        bool hasPrev();
        void test();

        //FIXME these operators only work as prefix ops.
        BandedMatrixIterator<T>& operator++();
        BandedMatrixIterator<T>& operator--();
        T& operator*() const;
        std::pair<int, int> coordinates();
    private:
        T* _dat;
        std::vector<MatrixCol <T> > _cols;
        MatrixCol<T> _currCol;
        int _size;
        int _x;
        int _y;
        int _index;
};

template <class S>
class MatrixCol
{
    public:
        MatrixCol();
        MatrixCol(int, int, S*);
        S& operator[](const int);
    protected:
        friend class BandedMatrix<S>;
        friend class BandedMatrixIterator<S>;
        S* _dat;
        int _offset;
        int _length;
};

template <class T>
class BandedMatrix
{

    public:
        BandedMatrix();
        BandedMatrix(int, int);
        ~BandedMatrix();
        MatrixCol<T> operator[](const int);
        const BandedMatrixIterator<T> begin();
        const BandedMatrixIterator<T> end();
        bool inbounds(int, int);
        int rows(){ return _numRows; }
        int cols(){ return _numCols; }
        int size();
        int resize(bool, bool);
    private:
        T* _dat; //TODO use shared swap space later;
        T  _val;
        std::vector<MatrixCol<T> > _cols;
        std::vector<int> _startPos; 
        void makeCols();
        T* getPtr(int, int);

        int _numRows;
        int _numCols;

        int _size;
        int _left;
        int _right;

        BandedMatrixIterator<T> _begin;
        BandedMatrixIterator<T> _end;
};

class BandedAligner {
    public:
        BandedAligner(std::string);
        void initialize(std::string);
        int step();
        int align();
        bool isAligned(){ return _aligned; }
        bool isInitialized(){ return _initialized; }
        int lowerBound(){ return _lowerBound; }
        int upperBound(){ return _upperBound; }
    private:
        void setBounds(int, int, int);
        std::string _ref;
        std::string _test;
        bool _aligned;
        bool _initialized;
        int _upperBound;
        int _lowerBound;
        BandedMatrix<int> _matrix;
};

#endif
