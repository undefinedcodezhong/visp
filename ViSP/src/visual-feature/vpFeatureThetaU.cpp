/****************************************************************************
 *
 * $Id: vpFeatureThetaU.cpp,v 1.14 2008-10-31 17:50:09 fspindle Exp $
 *
 * Copyright (C) 1998-2006 Inria. All rights reserved.
 *
 * This software was developed at:
 * IRISA/INRIA Rennes
 * Projet Lagadic
 * Campus Universitaire de Beaulieu
 * 35042 Rennes Cedex
 * http://www.irisa.fr/lagadic
 *
 * This file is part of the ViSP toolkit.
 *
 * This file may be distributed under the terms of the Q Public License
 * as defined by Trolltech AS of Norway and appearing in the file
 * LICENSE included in the packaging of this file.
 *
 * Licensees holding valid ViSP Professional Edition licenses may
 * use this file in accordance with the ViSP Commercial License
 * Agreement provided with the Software.
 *
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * Contact visp@irisa.fr if any conditions of this licensing are
 * not clear to you.
 *
 * Description:
 * ThetaU visual feature.
 *
 * Authors:
 * Eric Marchand
 *
 *****************************************************************************/


#include <visp/vpBasicFeature.h>
#include <visp/vpFeatureThetaU.h>
#include <visp/vpMath.h>

// Exception
#include <visp/vpException.h>
#include <visp/vpMatrixException.h>
#include <visp/vpFeatureException.h>

// Debug trace
#include <visp/vpDebug.h>


/*!
  \file vpFeatureThetaU.cpp
  \brief class that defines the thetaU visual feature
*/
/*

attributes and members directly related to the vpBasicFeature needs
other functionalities are usefull but not mandatory

*/

/*! 

  Initialise the memory space requested for 3D \f$ \theta u \f$ visual
  feature.
*/
void
vpFeatureThetaU::init()
{
  //feature dimension
  dim_s = 3 ;

  // memory allocation
  s.resize(dim_s) ;
}

/*! 
  Default constructor.

  \param r [in] : The rotation representation of the \f$ \theta u\f$
  visual feature.

*/
vpFeatureThetaU::vpFeatureThetaU(vpFeatureThetaURotationRepresentationType r):
  vpBasicFeature()
{
  //vpTRACE("0x%x", this);
  init() ;

  // kind of rotation representation
  rotation = r;
}

/*!

  Constructor that build a 3D \f$ \theta u \f$ visual feature from a
  rotation matrix \f$ R \f$ that represent the rotation that
  the camera has to achieve.

  \param R [in] : Rotation that the camera has to achieve. Depending
  on r this rotation represent either the rotation that the camera has
  to achieve to move from the desired camera frame to the current one
  (\f$ ^{c^*}R_c\f$), or the rotation that the camera has to achieve to
  move from the current camera frame to the desired one (\f$
  ^{c}R_{c^*}\f$).

  \param r [in] : The rotation representation of R.

*/

vpFeatureThetaU::vpFeatureThetaU(vpRotationMatrix &R, 
				 vpFeatureThetaURotationRepresentationType r):
  vpBasicFeature()
{
  init() ;
  
  vpThetaUVector tu(R) ;
  buildFrom(tu) ;

  // kind of rotation representation
  rotation = r;
}

/*!

  Constructor that build a 3D \f$ \theta u \f$ visual feature from an
  homogeneous matrix \f$ M \f$ that represent the displacement that
  the camera has to achieve.

  \param M [in] : Homogeneous transformation that describe the
  movement that the camera has to achieve. Only the rotational part of
  this homogeneous transformation is taken into
  consideration. Depending on r the rotation represent either the
  rotation that the camera has to achieve to move from the desired
  camera frame to the current one (\f$ ^{c^*}R_c\f$), or the rotation
  that the camera has to achieve to move from the current camera frame
  to the desired one (\f$ ^{c}R_{c^*}\f$).

  \param r [in] : The rotation representation of M.


*/
vpFeatureThetaU::vpFeatureThetaU(vpHomogeneousMatrix &M, 
				 vpFeatureThetaURotationRepresentationType r):
 vpBasicFeature()
{
  init() ;
  vpRotationMatrix R ;
  M.extract(R)  ;
  vpThetaUVector tu(R) ;
  buildFrom(tu) ;

  // kind of rotation representation
  rotation = r;
}

/*!

  Build a 3D visual feature from a \f$ \theta u \f$ vector that
  represent the rotation \f$ R \f$ the camera has to achieve.

  \param tu [in] : Rotation that the camera has to achieve in \f$
  \theta u \f$ axis/vector representation. Depending on the rotation
  representation type
  (vpFeatureThetaU::vpFeatureThetaURotationRepresentationType) used to
  construct this object, the parameter \e tu represents either the
  rotation that the camera has to achieve to move from the desired
  camera frame to the current one (\f$ ^{c^*}R_c\f$), or the rotation
  that the camera has to achieve to move from the current camera frame
  to the desired one (\f$ ^{c}R_{c^*}\f$).

*/
void
vpFeatureThetaU::buildFrom(vpThetaUVector &tu)
{
  s[0] = tu[0] ;
  s[1] = tu[1] ;
  s[2] = tu[2] ;
}

/*!
  Build a 3D \f$ \theta u \f$ visual feature from a
  rotation matrix \f$ R \f$ that represent the rotation that
  the camera has to achieve.

  \param R [in] : Rotation that the camera has to achieve. Depending
  on the rotation representation type
  (vpFeatureThetaU::vpFeatureThetaURotationRepresentationType) used to
  construct this object, the parameter \e R represents either the
  rotation that the camera has to achieve to move from the desired
  camera frame to the current one (\f$ ^{c^*}R_c\f$), or the rotation
  that the camera has to achieve to move from the current camera frame
  to the desired one (\f$ ^{c}R_{c^*}\f$).

*/
void
vpFeatureThetaU::buildFrom(const vpRotationMatrix &R)
{
    vpThetaUVector tu(R) ;
    buildFrom(tu) ;
}

/*!
  Build a 3D \f$ \theta u \f$ visual feature from an
  homogeneous matrix \f$ M \f$ that represent the displacement that
  the camera has to achieve.

  \param M [in] : Homogeneous transformation that describe the
  movement that the camera has to achieve. Only the rotational part of
  this homogeneous transformation is taken into consideration.
  Depending on the rotation representation type
  (vpFeatureThetaU::vpFeatureThetaURotationRepresentationType) used to
  construct this object, the parameter \e M represents either the
  rotation that the camera has to achieve to move from the desired
  camera frame to the current one (\f$ ^{c^*}R_c\f$), or the rotation
  that the camera has to achieve to move from the current camera frame
  to the desired one (\f$ ^{c}R_{c^*}\f$).


*/
void
vpFeatureThetaU::buildFrom(const vpHomogeneousMatrix &M)
{
    vpRotationMatrix R ;
    M.extract(R)  ;
    vpThetaUVector tu(R) ;
    buildFrom(tu) ;
}

/*!

  Initialise the current 3D visual feature \f$ s\f$ with the \f$\theta
  u_x \f$ component.

  \param tu_x : \f$\theta u_x \f$ component.
  \sa get_TUx()
*/
void vpFeatureThetaU::set_TUx(const double tu_x)
{
    s[0] = tu_x ;
}
/*!
  Return the \f$\theta u_x \f$ visual feature value.

*/
double vpFeatureThetaU::get_TUx()  const
{
    return s[0] ;
}

/*!

  Initialise the current 3D visual feature \f$ s\f$ with the \f$\theta
  u_y \f$ component.

  \param tu_y : \f$\theta u_y \f$ component.
  \sa get_TUy()
*/
void vpFeatureThetaU::set_TUy(const double tu_y)
{
    s[1] = tu_y ;
}

/*!
  Return the \f$\theta u_y \f$ visual feature value.

*/
double vpFeatureThetaU::get_TUy()   const
{
    return s[1] ;
}

/*!

  Initialise the current 3D visual feature \f$ s\f$ with the \f$\theta
  u_z \f$ component.

  \param tu_z : \f$\theta u_z \f$ component.
  \sa get_TUz()
*/
void
vpFeatureThetaU::set_TUz(const double tu_z)
{
    s[2] = tu_z ;
}

/*!
  Return the \f$\theta u_z \f$ visual feature value.

*/
double
vpFeatureThetaU::get_TUz() const
{
    return  s[2]  ;
}


/*!

  Compute and return the interaction matrix \f$ L \f$ from
  a subset (\f$ \theta u_x, \theta u_y, \theta u_z\f$) of the possible
  \f$ \theta u \f$ features that represent the 3D rotation
  \f$^{c^*}R_c\f$ or \f$^{c}R_{c^*}\f$, with

  \f[ L = [ 0_3 \; L_{\theta u}] \f] 

  See the vpFeatureThetaU class description for the equations of
  \f$L_{\theta u}\f$.

  \param select : Selection of a subset of the possible \f$ \theta u \f$
  features. 
  - To compute the interaction matrix for all the three \f$ \theta u \f$ 
    features use vpBasicFeature::FEATURE_ALL. In that case the dimention of the
    interaction matrix is \f$ [3 \times 6] \f$
  - To compute the interaction matrix for only one of the \f$ \theta u \f$ 
    component feature (\f$\theta u_x, \theta u_y, \theta u_z\f$) use one of the
    corresponding function selectTUx(), selectTUy() or selectTUz(). In
    that case the returned interaction matrix is \f$ [1 \times 6] \f$
    dimension.

  \return The interaction matrix computed from the \f$ \theta u \f$
  features that represent either the rotation \f$^{c^*}R_c\f$ or the
  rotation \f$^{c}R_{c^*}\f$.

  The code below shows how to compute the interaction matrix
  associated to the visual feature \f$s = \theta u_x \f$. 

  \code
  vpRotationMatrix cdMc;

  // Creation of the current feature s
  vpFeatureThetaU s(vpFeatureThetaU::cdRc);
  s.buildFrom(cdMc);

  vpMatrix L_x =  s.interaction( vpFeatureThetaU::selectTUx() );
  \endcode

  The code below shows how to compute the interaction matrix
  associated to the \f$s = (\theta u_x, \theta u_y) \f$
  subset visual feature:

  \code
  vpMatrix L_xy =  s.interaction( vpFeatureThetaU::selectTUx() | vpFeatureThetaU::selectTUy() );
  \endcode

  L_xy is here now a 2 by 6 matrix. The first line corresponds to
  the \f$ \theta u_x \f$ visual feature while the second one to the \f$
  \theta u_y \f$ visual feature.

  It is also possible to build the interaction matrix from all the \f$
  \theta u \f$ components by:

  \code
  vpMatrix L_xyz =  s.interaction( vpBasicFeature::FEATURE_ALL );
  \endcode

  In that case, L_xyz is a 3 by 6 interaction matrix where the last
  line corresponds to the \f$ \theta u_z \f$ visual feature.

*/
vpMatrix
vpFeatureThetaU::interaction(const int select) const
{

  vpMatrix L ;
  L.resize(0,6) ;

  vpMatrix Lw(3,3) ;
  Lw.setIdentity() ;

  double  theta = sqrt(s.sumSquare()) ;

  vpColVector u(3)  ;
  for (int i=0 ; i < 3 ; i++) u[i] = s[i]/theta ;

  vpMatrix skew_u ;
  skew_u = vpColVector::skew(u) ;

  if (rotation == cdRc) {
    if (theta < 1e-6) {
      Lw.setIdentity() ;
    }
    else {
      Lw += theta/2.0*skew_u 
	+ (1-vpMath::sinc(theta)/vpMath::sqr(vpMath::sinc(theta/2.0)))
	*skew_u*skew_u ;
    }
  }
  else {
    if (theta < 1e-6) {
      Lw = -Lw ;
    }
    else {
      Lw = -Lw + theta/2.0*skew_u 
	- (1-vpMath::sinc(theta)/vpMath::sqr(vpMath::sinc(theta/2.0)))
	*skew_u*skew_u ;

    }
  }

  //This version is a simplification
  if (vpFeatureThetaU::selectTUx() & select )
    {
      vpMatrix Lx(1,6) ;

      Lx[0][0] = 0 ;    Lx[0][1] = 0 ;    Lx[0][2] = 0 ;
      for (int i=0 ; i < 3 ; i++) Lx[0][i+3] = Lw[0][i] ;


      L = vpMatrix::stackMatrices(L,Lx) ;
    }

  if (vpFeatureThetaU::selectTUy() & select )
    {
      vpMatrix Ly(1,6) ;

      Ly[0][0] = 0 ;    Ly[0][1] = 0 ;    Ly[0][2] = 0 ;
      for (int i=0 ; i < 3 ; i++) Ly[0][i+3] = Lw[1][i] ;

      L = vpMatrix::stackMatrices(L,Ly) ;
    }

  if (vpFeatureThetaU::selectTUz() & select )
    {
      vpMatrix Lz(1,6) ;

      Lz[0][0] = 0 ;    Lz[0][1] = 0 ;    Lz[0][2] = 0 ;
      for (int i=0 ; i < 3 ; i++) Lz[0][i+3] = Lw[2][i] ;

      L = vpMatrix::stackMatrices(L,Lz) ;
    }

  return L ;
}

/*!
  
  Compute the error \f$ (s-s^*)\f$ between the current and the desired
  visual features from a subset of the possible features.

  Since this visual feature \f$ s \f$ represent the rotation from the desired
  camera frame to the desired one \f$^{c^*}R_{c} \f$, the desired
  visual feature \f$ s^* \f$ should be zero. Thus, the error is here
  equal to the current visual feature \f$ s \f$.

  \param s_star : Desired visual visual feature that should be equal to zero.

  \param select : The error can be computed for a selection of a
  subset of the possible \f$ \theta u \f$ features.
  - To compute the error for all the three \f$ \theta u \f$ features use
    vpBasicFeature::FEATURE_ALL. In that case the error vector is a 3 
    dimention column vector.
  - To compute the error for only one of the \f$ \theta u \f$ component 
    feature (\f$ \theta u_x, \theta u_y, \theta u_z\f$) use one of the
    corresponding function selectTUx(), selectTUy() or selectTUz(). In
    that case the error vector is a 1 dimention column vector.

  \return The error \f$ (s-s^*)\f$ between the current and the desired
  visual feature.

  \exception vpFeatureException::badInitializationError : If the
  desired visual feature \f$ s^* \f$ is not equal to zero.

  The code below shows how to use this method to manipulate the \f$\theta u_z \f$ subset:

  \code
  // Creation of the current feature s
  vpFeatureThetaU s(vpFeatureThetaU::cdRc);
  s.set_TUz(0.3);

  // Creation of the desired feature s^*. By default this feature is 
  // initialized to zero
  vpFeatureThetaU s_star(vpFeatureThetaU::cdRc); 

  // Compute the interaction matrix for the ThetaU_z feature
  vpMatrix L_z =  s.interaction( vpFeatureThetaU::selectTUz() );

  // Compute the error vector (s-s^*) for the ThetaU_z feature
  s.error(s_star, vpFeatureThetaU::selectTUz());
  \endcode
*/
vpColVector
vpFeatureThetaU::error(const vpBasicFeature &s_star,
		       const int select)
{

  if (fabs(s_star.get_s().sumSquare()) > 1e-6)
  {

    vpERROR_TRACE("s* should be zero ! ") ;
        throw(vpFeatureException(vpFeatureException::badInitializationError,
				 "s* should be zero !")) ;

  }

    vpColVector e(0) ;


    if (vpFeatureThetaU::selectTUx() & select )
    {
      vpColVector ex(1) ;
      ex[0] = s[0]  ;
      e = vpMatrix::stackMatrices(e,ex) ;
    }

    if (vpFeatureThetaU::selectTUy() & select )
    {
      vpColVector ey(1) ;
      ey[0] = s[1] ;
      e = vpMatrix::stackMatrices(e,ey) ;
    }

    if (vpFeatureThetaU::selectTUz() & select )
    {
      vpColVector ez(1) ;
      ez[0] = s[2] ;
      e = vpMatrix::stackMatrices(e,ez) ;
    }
    return e ;
}

/*!
  Print to stdout the values of the current visual feature \f$ s \f$.

  \param select : Selection of a subset of the possible \f$ \theta u
  \f$ features.
  - To print all the three \f$ \theta u \f$ features use
    vpBasicFeature::FEATURE_ALL. 
  - To print only one of the \f$ \theta u \f$ component 
    feature (\f$ \theta u_x, \theta u_y, \theta u_z\f$) use one of the
    corresponding function selectTUx(), selectTUy() or selectTUz().

  \code
  vpThetaUVector tu; // Current visual feature s
  tu[0] =0.1;
  tu[1] =0.2;
  tu[2] =0.3;
  
  // Creation of the current feature s
  vpFeatureThetaU s(vpFeatureThetaU::cdRc);
  s.buildFrom(tu);

  s.print(); // print all the 3 components of the feature
  s.print(vpFeatureThetaU::selectTUz()); // print only the ThetaU_z component

  \endcode
*/
void
vpFeatureThetaU::print(const int select) const
{
  std::cout <<"ThetaU: ";
  if (vpFeatureThetaU::selectTUx() & select ) {
    std::cout << s[0] << " ";
  }
  if (vpFeatureThetaU::selectTUy() & select ) {
    std::cout << s[1] << " ";
  }
  if (vpFeatureThetaU::selectTUz() & select ) {
    std::cout << s[2] << " ";
  }
  std::cout << std::endl;
}

vpFeatureThetaU *vpFeatureThetaU::duplicate() const
{
  vpFeatureThetaU *feature;
  if (rotation == cdRc) 
    feature  = new vpFeatureThetaU(vpFeatureThetaU::cdRc) ;
  else //if (rotation == cRcd
    feature  = new vpFeatureThetaU(vpFeatureThetaU::cRcd) ;
    
  return feature ;
}

/*!

  Not implemented.

*/
void
vpFeatureThetaU::display(const vpCameraParameters &/* cam */,
			 vpImage<unsigned char> &/* I */,
			 vpColor::vpColorType /* color */) const
{
  static int firsttime =0 ;

  if (firsttime==0)
  {
    firsttime=1 ;
    vpERROR_TRACE("not implemented") ;
    // Do not throw and error since it is not subject
    // to produce a failure
  }
}
/*!

  Not implemented.

 */
void
vpFeatureThetaU::display(const vpCameraParameters &/* cam */,
                         vpImage<vpRGBa> &/* I */,
                         vpColor::vpColorType /* color */) const
{
  static int firsttime =0 ;

  if (firsttime==0)
  {
    firsttime=1 ;
    vpERROR_TRACE("not implemented") ;
    // Do not throw and error since it is not subject
    // to produce a failure
  }
}

/*
 * Local variables:
 * c-basic-offset: 2
 * End:
 */
