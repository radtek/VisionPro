/***********************************************************
 * File generated by the HALCON-Compiler hcomp version 19.11
 * Usage: Interface to C++
 *
 * Software by: MVTec Software GmbH, www.mvtec.com
 ***********************************************************/


#ifndef HCPP_HFUNCTION1D
#define HCPP_HFUNCTION1D

namespace HalconCpp
{

// Represents an instance of a 1d function.
class LIntExport HFunction1D : public HDataBase
{

public:

  // Create an uninitialized instance
  HFunction1D():HDataBase() {}

  // Copy constructor
  HFunction1D(const HFunction1D& source) : HDataBase(source) {}



/*****************************************************************************
 * Operator-based class constructors
 *****************************************************************************/

  // create_funct_1d_array: Create a function from a sequence of y values.
  explicit HFunction1D(const HTuple& YValues);

  // create_funct_1d_array: Create a function from a sequence of y values.
  explicit HFunction1D(double YValues);

  // create_funct_1d_pairs: Create a function from a set of (x,y) pairs.
  explicit HFunction1D(const HTuple& XValues, const HTuple& YValues);

  // create_funct_1d_pairs: Create a function from a set of (x,y) pairs.
  explicit HFunction1D(double XValues, double YValues);


/*****************************************************************************
 * Operator overloads (non-member overloads reside in HOperatorOverloads.h)  *
 *****************************************************************************/

  // Negate function
  HFunction1D operator - () const;

  // Invert function
  HFunction1D operator ! () const;


  /***************************************************************************
   * Operators                                                               *
   ***************************************************************************/

  // Plot a function using gnuplot.
  void GnuplotPlotFunct1d(const HGnuplot& GnuplotFileID) const;

  // Compose two functions.
  HFunction1D ComposeFunct1d(const HFunction1D& Function2, const HString& Border) const;

  // Compose two functions.
  HFunction1D ComposeFunct1d(const HFunction1D& Function2, const char* Border) const;

#ifdef _WIN32
  // Compose two functions.
  HFunction1D ComposeFunct1d(const HFunction1D& Function2, const wchar_t* Border) const;
#endif

  // Calculate the inverse of a function.
  HFunction1D InvertFunct1d() const;

  // Calculate the derivatives of a function.
  HFunction1D DerivateFunct1d(const HString& Mode) const;

  // Calculate the derivatives of a function.
  HFunction1D DerivateFunct1d(const char* Mode) const;

#ifdef _WIN32
  // Calculate the derivatives of a function.
  HFunction1D DerivateFunct1d(const wchar_t* Mode) const;
#endif

  // Calculate the local minimum and maximum points of a function.
  void LocalMinMaxFunct1d(const HString& Mode, const HString& Interpolation, HTuple* Min, HTuple* Max) const;

  // Calculate the local minimum and maximum points of a function.
  void LocalMinMaxFunct1d(const char* Mode, const char* Interpolation, HTuple* Min, HTuple* Max) const;

#ifdef _WIN32
  // Calculate the local minimum and maximum points of a function.
  void LocalMinMaxFunct1d(const wchar_t* Mode, const wchar_t* Interpolation, HTuple* Min, HTuple* Max) const;
#endif

  // Calculate the zero crossings of a function.
  HTuple ZeroCrossingsFunct1d() const;

  // Multiplication and addition of the y values.
  HFunction1D ScaleYFunct1d(double Mult, double Add) const;

  // Negation of the y values.
  HFunction1D NegateFunct1d() const;

  // Absolute value of the y values.
  HFunction1D AbsFunct1d() const;

  // Return the value of a function at an arbitrary position.
  HTuple GetYValueFunct1d(const HTuple& X, const HString& Border) const;

  // Return the value of a function at an arbitrary position.
  double GetYValueFunct1d(double X, const HString& Border) const;

  // Return the value of a function at an arbitrary position.
  double GetYValueFunct1d(double X, const char* Border) const;

#ifdef _WIN32
  // Return the value of a function at an arbitrary position.
  double GetYValueFunct1d(double X, const wchar_t* Border) const;
#endif

  // Access a function value using the index of the control points.
  void GetPairFunct1d(const HTuple& Index, HTuple* X, HTuple* Y) const;

  // Access a function value using the index of the control points.
  void GetPairFunct1d(Hlong Index, double* X, double* Y) const;

  // Number of control points of the function.
  Hlong NumPointsFunct1d() const;

  // Smallest and largest y value of the function.
  void YRangeFunct1d(double* YMin, double* YMax) const;

  // Smallest and largest x value of the function.
  void XRangeFunct1d(double* XMin, double* XMax) const;

  // Access to the x/y values of a function.
  void Funct1dToPairs(HTuple* XValues, HTuple* YValues) const;

  // Sample a function equidistantly in an interval.
  HFunction1D SampleFunct1d(const HTuple& XMin, const HTuple& XMax, const HTuple& XDist, const HString& Border) const;

  // Sample a function equidistantly in an interval.
  HFunction1D SampleFunct1d(double XMin, double XMax, double XDist, const HString& Border) const;

  // Sample a function equidistantly in an interval.
  HFunction1D SampleFunct1d(double XMin, double XMax, double XDist, const char* Border) const;

#ifdef _WIN32
  // Sample a function equidistantly in an interval.
  HFunction1D SampleFunct1d(double XMin, double XMax, double XDist, const wchar_t* Border) const;
#endif

  // Transform a function using given transformation parameters.
  HFunction1D TransformFunct1d(const HTuple& Params) const;

  // Calculate transformation parameters between two functions.
  HTuple MatchFunct1dTrans(const HFunction1D& Function2, const HString& Border, const HTuple& ParamsConst, const HTuple& UseParams, double* ChiSquare, HTuple* Covar) const;

  // Calculate transformation parameters between two functions.
  HTuple MatchFunct1dTrans(const HFunction1D& Function2, const char* Border, const HTuple& ParamsConst, const HTuple& UseParams, double* ChiSquare, HTuple* Covar) const;

#ifdef _WIN32
  // Calculate transformation parameters between two functions.
  HTuple MatchFunct1dTrans(const HFunction1D& Function2, const wchar_t* Border, const HTuple& ParamsConst, const HTuple& UseParams, double* ChiSquare, HTuple* Covar) const;
#endif

  // Compute the distance of two functions.
  HTuple DistanceFunct1d(const HFunction1D& Function2, const HTuple& Mode, const HTuple& Sigma) const;

  // Compute the distance of two functions.
  HTuple DistanceFunct1d(const HFunction1D& Function2, const HString& Mode, double Sigma) const;

  // Compute the distance of two functions.
  HTuple DistanceFunct1d(const HFunction1D& Function2, const char* Mode, double Sigma) const;

#ifdef _WIN32
  // Compute the distance of two functions.
  HTuple DistanceFunct1d(const HFunction1D& Function2, const wchar_t* Mode, double Sigma) const;
#endif

  // Smooth an equidistant 1D function with a Gaussian function.
  HFunction1D SmoothFunct1dGauss(double Sigma) const;

  // Compute the positive and negative areas of a function.
  double IntegrateFunct1d(HTuple* Negative) const;

  // Read a function from a file.
  void ReadFunct1d(const HString& FileName);

  // Read a function from a file.
  void ReadFunct1d(const char* FileName);

#ifdef _WIN32
  // Read a function from a file.
  void ReadFunct1d(const wchar_t* FileName);
#endif

  // Write a function to a file.
  void WriteFunct1d(const HString& FileName) const;

  // Write a function to a file.
  void WriteFunct1d(const char* FileName) const;

#ifdef _WIN32
  // Write a function to a file.
  void WriteFunct1d(const wchar_t* FileName) const;
#endif

  // Create a function from a sequence of y values.
  void CreateFunct1dArray(const HTuple& YValues);

  // Create a function from a sequence of y values.
  void CreateFunct1dArray(double YValues);

  // Create a function from a set of (x,y) pairs.
  void CreateFunct1dPairs(const HTuple& XValues, const HTuple& YValues);

  // Create a function from a set of (x,y) pairs.
  void CreateFunct1dPairs(double XValues, double YValues);

  // Smooth an equidistant 1D function by averaging its values.
  HFunction1D SmoothFunct1dMean(Hlong SmoothSize, Hlong Iterations) const;

};

}

#endif
