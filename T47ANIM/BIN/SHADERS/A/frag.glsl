#version 330

layout(location = 0) out vec4 OutColor;

in vec4 DrawColor;
in vec3 DrawPos;
in vec3 DrawN;

uniform float Time;
uniform float CamX;
uniform float CamY;
uniform float CamZ;

void main( void )
{
  vec3 c = vec3(0, 0, 0);
  vec3 L = normalize(vec3(1, sin(Time), 1));
  vec3 N = normalize(DrawN);
  float nl = dot(N, L);
  vec3 color = DrawColor.xyz;

  if (nl < 0.1)
    nl = 0.1;

  c = c + nl * color;

  vec3 Cam = vec3(CamX, CamY, CamZ);
  vec3 V = normalize(Cam - DrawPos);
  vec3 R = reflect(-V, N);
  float rl = dot(R, L);
  if (nl > 0.1 && rl > 0.000001)
    c += pow(rl, 47) * vec3(1, 1, 1);

  OutColor = vec4(c, 1);
}
