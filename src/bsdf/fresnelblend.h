/*
    This file is a part of SORT(Simple Open Ray Tracing), an open-source cross
    platform physically based renderer.
 
    Copyright (c) 2011-2018 by Cao Jiayin - All rights reserved.
 
    SORT is a free software written for educational purpose. Anyone can distribute
    or modify it under the the terms of the GNU General Public License Version 3 as
    published by the Free Software Foundation. However, there is NO warranty that
    all components are functional in a perfect manner. Without even the implied
    warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
    General Public License for more details.
 
    You should have received a copy of the GNU General Public License along with
    this program. If not, see <http://www.gnu.org/licenses/gpl-3.0.html>.
 */

#pragma once

#include "bxdf.h"
#include "microfacet.h"

//! @brief FresnelBlend brdf.
/**
 * An Anisotropic Phong BRDF Model
 * http://www.irisa.fr/prive/kadi/Lopez/ashikhmin00anisotropic.pdf
 * This BRDF model has two layer, specular and diffuse.
 * Unlike the modern PBR model ( microfacet + diffuse ), this model also counts fresnel effect when blending the two layer
 */
class FresnelBlend : public Bxdf
{
public:
	//! Contstructor
    //! @param diffuse          Direction-hemisphere reflection for diffuse.
    //! @param specular         Direction-hemisphere reflection for specular.
    //! @param d                Normal distribution function.
	FresnelBlend( const Spectrum& diffuse , const Spectrum& specular , const MicroFacetDistribution* d );
	
    //! Evaluate the BRDF
    //! @param wo   Exitance direction in shading coordinate.
    //! @param wi   Incomiing direction in shading coordinate.
    //! @return     The evaluted BRDF value.
    Spectrum f( const Vector& wo , const Vector& wi ) const override;
	
    //! @brief Importance sampling for the fresnel brdf.
    //! @param wo   Exitance direction in shading coordinate.
    //! @param wi   Incomiing direction in shading coordinate.
    //! @param bs   Sample for bsdf that holds some random variables.
    //! @param pdf  Probability density of the selected direction.
    //! @return     The evaluted BRDF value.
    Spectrum sample_f( const Vector& wo , Vector& wi , const BsdfSample& bs , float* pdf ) const override;
    
    //! @brief Evalute the pdf of an existance direction given the incoming direction.
    //! @param wo   Exitance direction in shading coordinate.
    //! @param wi   Incomiing direction in shading coordinate.
    //! @return     The probabilty of choosing the out-going direction based on the incoming direction.
    float Pdf( const Vector& wo , const Vector& wi ) const override;
    
private:
	const Spectrum D , S;                           /**< Direction-Hemisphere reflectance and transmittance. */
    const MicroFacetDistribution* distribution;     /**< Normal Distribution Function. >**/
};
