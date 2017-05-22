#pragma once

#include <valarray>




template <typename valuetype>
class Matrix {
 private:
  size_t this_rowsize;  // row length
  size_t this_colsize;  // column length
  std::valarray<valuetype> this_data;

 public:

  // constructors
	Matrix()
    : this_rowsize(0)
    , this_colsize(0)
  {}

  Matrix( const size_t in_rowsize, const size_t in_colsize )
    : this_rowsize( in_rowsize )
    , this_colsize( in_colsize )
  {
    this_data.resize( this_rowsize * this_colsize );
  }

  Matrix( const size_t in_rowsize, const size_t in_colsize, const valuetype initialize_by )
    : this_rowsize( in_rowsize )
    , this_colsize( in_colsize )
  {
    this_data.resize( this_rowsize * this_colsize );
    this_data = initialize_by;
  }

  // copy constructor
  Matrix( const Matrix<valuetype>& from )
    : this_rowsize( from.rowsize() )
    , this_colsize( from.colsize() )
  {
    this_data.resize( this_rowsize * this_colsize );
    this_data = from.data();
  }

  // destructor
  ~Matrix() {}

  // getter
  size_t rowsize() const { return this_rowsize; }
  size_t colsize() const { return this_colsize; }
  std::valarray<valuetype> data() const { return this_data; }
  std::valarray<valuetype>& data() { return this_data; }

  // get element
  valuetype at( const size_t row_index, const size_t col_index ) const {
    return this_data[ row_index * colsize() + col_index ];
  }
  valuetype& at( const size_t row_index, const size_t col_index ) {
    return this_data[ row_index * colsize() + col_index ];
  }

  // get row
  std::valarray<valuetype> row( const size_t row_index ) const {
    std::slice s( row_index * colsize(), colsize(), 1 );
    return std::valarray<valuetype>( this_data[ s ] );
  }
  std::slice_array<valuetype> row( const size_t row_index ) {
    std::slice s( row_index * colsize(), colsize(), 1 );
    return this_data[ s ];
  }

  std::valarray<valuetype> lastrow() const {
    return row( rowsize() - 1 );
  }
  std::slice_array<valuetype> lastrow() {
    return row( rowsize() - 1 );
  }

  // get column
  std::valarray<valuetype> col( const size_t col_index ) const {
    std::slice s( col_index, rowsize(), colsize() );
    return std::valarray<valuetype>( this_data[ s ] );
  }
  std::slice_array<valuetype> col( const size_t col_index ) {
    std::slice s( col_index, rowsize(), colsize() );
    return this_data[ s ];
  }

  std::valarray<valuetype> lastcol() const {
    return col( colsize() - 1 );
  }
  std::slice_array<valuetype> lastcol() {
    return col( colsize() - 1 );
  }


  // print
  template <typename T>  friend
  std::ostream& operator<<( std::ostream& ost, const std::valarray<T>& va ) {
    ost << "[ ";
    for ( size_t i = 0; i < va.size() - 1; ++i ) {
      ost << va[i] << ", ";
    }
    ost << va[ va.size() - 1 ] << " ]";
    return ost;
  }

  template <typename T>  friend
  std::ostream& operator<<( std::ostream& ost, const Matrix<T>& mtrx ) {
    ost << "[ " << mtrx.row(0) << std::endl;
    for ( size_t i = 1; i < mtrx.rowsize() - 1; ++i ) {
      ost << "  " << mtrx.row(i) << std::endl;
    }
    ost << "  " << mtrx.lastrow() << " ]" << std::endl;
    return ost;
  }


  // assignment operator
	Matrix& operator=( const Matrix& Mright ) {
  	if( this == &Mright ) return *this;  // self assignment check
    this_rowsize = Mright.rowsize();
    this_colsize = Mright.colsize();
    this_data.resize( this_rowsize * this_colsize );
    this_data = Mright.data();
    return *this;
  }


  // equality
	bool operator==( const Matrix& Mright ) const {
    if ( this->rowsize() != Mright.rowsize() ) return false;
    if ( this->colsize() != Mright.colsize() ) return false;
    const std::valarray<bool> result = ( this->data() == Mright.data() );  // autoだと失敗
    return std::all_of( std::begin( result ), std::end( result ), [] ( bool b ) { return b; } );
  }
	bool operator!=( const Matrix& Mright ) const {
    return !( *this == Mright );
  }


  // unary operators (+,-)
  Matrix<valuetype> operator+() const {
    return Matrix<valuetype>(this);
  }
  Matrix<valuetype> operator-() const {
    Matrix<valuetype> M( *this );
    M.data() = -( this->data() );
    return M;
  }


  // binary operators (+, -, *)
  template <typename T>  friend
	Matrix<T> operator+( const Matrix<T>& M1, const Matrix<T>& M2 ) {
    Matrix<T> result( M1 );
    result.data() += M2.data();
    return result;
  }
  template <typename T>  friend
	Matrix<T> operator-( const Matrix<T>& M1, const Matrix<T>& M2 ) {
    Matrix<T> result( M1 );
    result.data() -= M2.data();
    return result;
  }
  template <typename T>  friend
	Matrix<T> operator*( const Matrix<T>& M1, const Matrix<T>& M2 ) {
    Matrix<valuetype> result( M1.rowsize(), M2.colsize() );
    for ( size_t i = 0; i < result.rowsize(); ++i ) {
      for ( size_t j = 0; j < result.colsize(); ++j ) {
        result.at(i,j) = ( M1.row(i) * M2.col(j) ).sum();
      }
    }
    return result;
  }

  // compound assignment(+=, -=)
	void operator+=( const Matrix& Mright ) {
    this->data() += Mright.data();
  }
	void operator-=( const Matrix& Mright ) {
    this->data() -= Mright.data();
  }


  // multiplication/division with number
  // ToDo : use apply() ?
	template <typename T> friend
	Matrix<T> operator*( const T num, const Matrix<T>& Mright ) {
    Matrix<T> result( Mright.rowsize(), Mright.colsize() );
    result.data() = Mright.data() * std::valarray<T>( num, Mright.data().size() );
    return result;
  }

	template <typename T> friend
	Matrix<T> operator*( const Matrix<T>& Mleft, const T num ) {
    Matrix<T> result( Mleft.rowsize(), Mleft.colsize() );
    result.data() = Mleft.data() * std::valarray<T>( num, Mleft.data().size() );
    return result;
  }

	template <typename T> friend
	void operator*=( Matrix<T>& Mleft, const T num ) {
    Mleft.data() = Mleft.data() * std::valarray<T>( num, Mleft.data().size() );
  }

	template <typename T> friend
	Matrix<T> operator/( const Matrix<T>& Mleft, const T num ) {
    Matrix<T> result( Mleft.rowsize(), Mleft.colsize() );
    result.data() = Mleft.data() / std::valarray<T>( num, Mleft.data().size() );
    return result;
  }

	template <typename T> friend
	void operator/=( Matrix<T>& Mleft, const T num ) {
    Mleft.data() = Mleft.data() / std::valarray<T>( num, Mleft.data().size() );
  }

  // multiplication with vector
	template <typename T>  friend
  std::valarray<T> operator*( const std::valarray<T>& V, const Matrix<T>& M ) {
    std::valarray<T> result;
    for ( size_t j = 0; j < M.colsize(); ++j ) {
      result[j] = ( V * M.col(j) ).sum();
    }
    return result;
  }

	template <typename T>  friend
  std::valarray<T> operator*( const Matrix<T>& M, const std::valarray<T>& V ) {
    std::valarray<T> result;
    for ( size_t i = 0; i < M.rowsize(); ++i ) {
      result[i] = ( M.col(i) * V ).sum();
    }
    return result;
  }


};



