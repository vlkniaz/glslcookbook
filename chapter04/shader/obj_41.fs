#version 410

in vec3 Position;
in vec3 Normal;
in highp vec3 Color;

uniform sampler2D BaseTex;
uniform sampler2D AlphaTex;
uniform float SilhouetteMode;

struct LightInfo {
  vec4 Position;  // Light position in eye coords.
  vec3 Intensity; // A,D,S intensity
};
uniform LightInfo Light;

struct MaterialInfo {
  vec3 Ka;            // Ambient reflectivity
  vec3 Kd;            // Diffuse reflectivity
  vec3 Ks;            // Specular reflectivity
  float Shininess;    // Specular shininess factor
};
uniform MaterialInfo Material;

layout( location = 0 ) out vec4 FragColor;

vec3 phongModel( vec3 pos, vec3 norm )
{
    vec3 s = normalize(vec3(Light.Position) - pos);
    vec3 v = normalize(-pos.xyz);
    vec3 r = reflect( -s, norm );
    vec3 ambient = Light.Intensity * Material.Ka;
    float sDotN = max( dot(s,norm), 0.0 );
    vec3 diffuse = Light.Intensity * Material.Kd * sDotN;
    vec3 spec = vec3(0.0);
    if( sDotN > 0.0 )
        spec = Light.Intensity * Material.Ks *
               pow( max( dot(r,v), 0.0 ), Material.Shininess );

    return ambient + diffuse + spec;
}

void main()
{
    vec4 baseColor = vec4(0.58, 0.44, 0.86, 1.0);
    
    if(min(min(Color.x, Color.y), Color.z) < 1.0/50.0 && SilhouetteMode < 1.0)
    {
        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
    else
    {
        FragColor = vec4( phongModel(Position,Normal), 1.0 ) * baseColor;
    }
}
