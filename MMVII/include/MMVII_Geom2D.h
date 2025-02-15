#ifndef  _MMVII_GEOM2D_H_
#define  _MMVII_GEOM2D_H_

namespace MMVII
{

/** \file MMVII_Geom2D.h
    \brief contain classes for geometric manipulation, specific to 2D space :
           2D line, 2D plane, rotation, ...
*/

     // Complex and  polar function dedicatde
///   Complex multiplication 
inline cPt2dr operator * (const cPt2dr &aP1,const cPt2dr & aP2)
{
   return cPt2dr(aP1.x()*aP2.x()-aP1.y()*aP2.y(),aP1.x()*aP2.y()+aP1.y()*aP2.x());
}
inline cPt2dr conj  (const cPt2dr &aP1) {return cPt2dr(aP1.x(),-aP1.y());}
inline cPt2dr inv   (const cPt2dr &aP1)
{  
   AssertNonNul(aP1); 
   return conj(aP1) / SqN2(aP1);
}
inline cPt2dr operator / (const cPt2dr &aP1,const cPt2dr & aP2) {return aP1 * inv(aP2);}


inline cPt2dr ToPolar(const cPt2dr & aP1)  ///<  From x,y to To rho,teta
{
   AssertNonNul(aP1);
   return  cPt2dr(hypot(aP1.x(),aP1.y()),atan2(aP1.y(),aP1.x()));
}

inline cPt2dr ToPolar(const cPt2dr & aP1,double aDefTeta)  ///<  With Def value 4 teta
{
    return IsNotNull(aP1) ? ToPolar(aP1) : cPt2dr(0,aDefTeta);
}
inline cPt2dr FromPolar(const double & aRho,const double & aTeta)
{
    return cPt2dr(aRho*cos(aTeta),aRho*sin(aTeta));
}
inline cPt2dr FromPolar(const cPt2dr & aP)
{
    return FromPolar(aP.x(),aP.y());
}

template <class Type> inline cPtxd<Type,2> PSymXY (const cPtxd<Type,2> & aP) 
{ 
    return cPtxd<Type,2>(aP.y(),aP.x()); 
}

/** This class represent 2D Homotetie , it can aussi be used for an non
   distorted camera with :
       * mTr -> principal point
       * mSc -> focale
*/

template <class Type>  class cHomot2D
{
      public :
          static constexpr int TheDim=2;
          typedef Type  TheType;
          typedef cPtxd<Type,2> tPt;

          static const int NbDOF() {return 3;}
          cHomot2D(const tPt & aTr,const Type & aSc)  :
              mTr (aTr),
              mSc (aSc)
          {
          }
          inline tPt  Value(const tPt & aP) const   {return mTr + aP * mSc;}
          inline tPt  Inverse(const tPt & aP) const {return (aP-mTr)/mSc  ;}
          cHomot2D<Type>  MapInverse() const {return cHomot2D<Type>(-mTr/mSc,1.0/mSc);}
      private :
          tPt mTr;
          Type mSc;
};

template <class Type>  class cSim2D
{
      public :
          typedef Type  TheType;
          static constexpr int TheDim=2;

          typedef cPtxd<Type,2> tPt;

          cSim2D(const tPt & aTr,const tPt & aSc)  :
              mTr (aTr),
              mSc (aSc)
          {
          }
          static const int NbDOF() {return 4;}

          inline tPt  Value(const tPt & aP) const {return mTr + aP * mSc;}
          inline tPt  Inverse(const tPt & aP) const {return (aP-mTr)/mSc  ;}

          cSim2D<Type>  MapInverse() const {return cSim2D<Type>(-mTr/mSc,tPt(1.0,0.0)/mSc);}
                
      private :
          tPt mTr;
          tPt mSc;
};


};

#endif  //  _MMVII_GEOM2D_H_
