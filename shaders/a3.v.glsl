#version 410 core

// uniform inputs
uniform mat4 mvpMatrix;                 // the precomputed Model-View-Projection Matrix
// add normal matrix
uniform mat3 normalMatrix;

//add the model matrix
uniform mat4 modelMtx;

// add light uniforms
uniform vec3 lightDirection;
uniform vec3 lightColor;

uniform vec3 materialColor;             // the material color for our vertex (& whole object)

uniform vec3 cameraPosition;

uniform vec3 pointLightPos;

uniform vec3 spotLightPos;

uniform vec3 spotLightLookatPoint;

uniform vec3 spotLightColor;

uniform int currentLight;

// attribute inputs
layout(location = 0) in vec3 vPos;      // the position of this specific vertex in object space
// add vertex normal
layout(location = 1) in vec3 vNormal;

// varying outputs
layout(location = 0) out vec3 color;    // color to apply to this vertex

void main() {

    vec3 viewDirection = normalize( cameraPosition - vPos);
    // transform & output the vertex in clip space
    gl_Position = mvpMatrix * vec4(vPos, 1.0);

    vec3 colorPoint;
    vec3 colorDir;
    vec3 colorSpot;

    // transform normal vector
    vec3 vNormalNew =  normalize( normalMatrix * vNormal);

    ////POINT LIGHT ////

    vec3 pointLightDirection = pointLightPos - vec3( modelMtx * vec4(vPos,1.0));

    vec3 lightVectorPoint = normalize(pointLightDirection);

    vec3 diffusePoint = 0.05 * (max(dot(lightVectorPoint,  vNormalNew),0)) * materialColor * lightColor;

    vec3 reflectancePoint =  0.05 * (-pointLightDirection + 2 * (max(dot(vNormalNew, pointLightDirection),0)) * vNormalNew);

    vec3 specularPoint = 0.05 *( pow(max(dot(reflectancePoint, viewDirection), 0),2)) * materialColor * lightColor;

    vec3 ambientPoint = 0.1  * materialColor * lightColor;

    colorPoint = diffusePoint + specularPoint + ambientPoint;
    //END OF POINT LIGHT////


    //DIRECTION LIGHT ////

    // compute Light vector
    vec3 lightVectorDir = -lightDirection / abs(lightDirection);

    // perform diffuse calculation
    vec3 diffuseDir = 0.05 * ( max(dot(lightVectorDir,  vNormalNew),0)) * materialColor * lightColor;

    vec3 reflectanceDir = 0.05 * (-lightDirection + 2 * (max(dot(vNormalNew, lightDirection),0)) * vNormalNew);
    vec3 specularDir = 0.05 *( pow(max(dot(reflectanceDir, viewDirection), 0),20)) * materialColor * lightColor;

    vec3 ambientDir = 0.1  * materialColor * lightColor;

    colorDir = diffuseDir + specularDir + ambientDir;
    //DIRECTIONAL LIGHT ////


    //SPOT LIGHT ////
    vec3 lightToVertexVec = vec3( modelMtx * vec4(vPos,1.0)) - spotLightPos;

    vec3 spotLightDirection = spotLightPos - vec3( modelMtx * vec4(vPos,1.0));

    // using the vector from the camera to vpos, and vec from vpos to camera get angle
    float angleBetweenLightAndVertex = dot(spotLightDirection, lightToVertexVec);

    vec3 diffuseSpot;
    vec3 specularSpot;
    vec3 ambientSpot;
    if(angleBetweenLightAndVertex >= 0.10 ){
        specularSpot = vec3(0.0,0.0,0.0);
        diffuseSpot = vec3(0.0,0.0,0.0);

        ambientSpot = 0.1 * lightColor;

    } else{
        vec3 lightVector = normalize(spotLightDirection);

        // perform diffuse calculation
        diffuseSpot = 0.05 * (spotLightColor * max(dot(lightVector,  vNormalNew),0)) * materialColor;

        vec3 reflectanceSpot =  0.05 * (-spotLightDirection + 2 * (max(dot(vNormalNew, spotLightDirection),0)) * vNormalNew);
        specularSpot = 0.05 *( pow(max(dot(reflectanceSpot, viewDirection), 0),2)) * materialColor * spotLightColor;

        ambientSpot = 0.1  * materialColor * spotLightColor;

    }

    colorSpot = specularSpot + ambientSpot + diffuseSpot;
    //SPOT LIGHT ////

    // assign the color for this vertex
    color = colorPoint + colorSpot + colorDir;
}
