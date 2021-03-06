#include<iostream>
#include<vector>
#include<stdexcept>

template<class T = long long>class matrix{
    std::vector<std::vector<T>> matrix_backing;
public:
    matrix(const matrix &in){
        this->matrix_backing = in.matrix_backing;
    }
    std::size_t row_size() const{
        return matrix_backing.size();
    }
    T& get(std::size_t row, std::size_t col){
        return matrix_backing.at(row).at(col);
    }

    T get(std::size_t row, std::size_t col) const{
        return matrix_backing.at(row).at(col);
    }
    std::size_t col_size() const{
        if(matrix_backing.size() != 0){
            return matrix_backing.at(0).size();
        }
        else return 0;
    }
    std::vector<T> getCol(std::size_t i) const{
        std::vector<T> result = std::vector<T>(this->col_size());
        for(std::size_t j = 0; j!=this->col_size(); ++j){
            result.at(i) = get(i,j);
        }
        return result;
    }

    std::vector<T> getRow(std::size_t i) const{
        return matrix_backing.at(i);
    }
    matrix(int rows, int collumns, int defaultVal):matrix_backing(rows,(std::vector<T>(collumns,defaultVal))){};

    matrix(int rows, int collumns):matrix_backing(rows,std::vector<T>(collumns)){};

    static matrix matrix_mult(const matrix& A, const matrix& B) {
        if(A.col_size() != B.row_size()){throw std::out_of_range("ERROR, MATRIX DIMENSIONS DO NOT MATCH FOR MULTIPLICATION");}
        matrix result = matrix(A.row_size(),B.col_size(),0);
        for(std::size_t i = 0; i!=result.row_size();++i){
            for(std::size_t j = 0; j!=result.col_size();++j){
                for(std::size_t k = 0; k!=A.col_size();++k){
                    result.get(i,j) +=A.get(i,k)*B.get(k,j);
                }
            }
        }
        return result;
    }

    static matrix matrix_pow(const matrix& A, int p){
        if(p == 1) return A;
        if(p%2 == 1){return matrix_mult(A,matrix_pow(A,p-1));}
        matrix x = matrix_pow(A,p/2);
        return matrix_mult(x,x);

    }
    friend matrix operator*(const matrix& A, const matrix& B){
        return matrix_mult(A,B);
    }
    friend std::ostream& operator<<(std::ostream& os, const matrix& in)
        {
            for(std::size_t i = 0; i!=in.row_size();++i){
                os<< "| ";
                for(std::size_t j = 0; j!=in.col_size();++j){
                    os << in.get(i,j) << " ";
                }
                os << "|" << std::endl;
            }
            return os;

        }

};

int main(){
     matrix<> test(3,3,3);
     std::cout << test << std::endl;

    matrix<> A(2,2,1);
    matrix<> B(2,1,2);
    A.get(0,1) = 10;
    B.get(0,0) = 5;
    std::cout << A << std::endl <<  B << std::endl;
    std::cout << A*B << std::endl;

    std::cout << "Begin Test" << std::endl;
    matrix<> T(2,2,1);

    T.get(0,0) = 0;
    std::cout << T << std::endl;
    matrix<> F1 (2,1,1);
    F1.getCol(0);
    F1.col_size();
    F1.row_size();
    std::cout << matrix<>::matrix_pow(T,5)*F1 << std::endl;

}
