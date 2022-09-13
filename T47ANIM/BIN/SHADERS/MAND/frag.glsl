#version 330

layout(location = 0) out vec4 OutColor;

in vec2 DP;

uniform float Time;

vec2 mul( vec2 z1, vec2 z2 )
{
  return vec2(z1.x * z2.x - z1.y * z2.y, z1.x * z2.y + z1.y * z2.x);
}

int mand( vec2 z, vec2 z0 )
{
  int n = 0;

  while (length(z) < 2 && n < 254)
    z = mul(z, z) + z0, n++;
  return n;
}

void main( void )
{
  int m = int(Time);
  int k;

  /*
  if (m / 3 % 2 == 0)
    k = mand(DP * 2, DP * 2);
  else
  */
  k = mand(DP * (2 + sin(Time)), vec2(0.40 + sin(3 * Time) * 0.18, 0.40 + sin(3 * Time * 1.1 + 3) * 0.18));
  OutColor = vec4(DP.x, mod(k / 255.0, 1), 0, 0);
}
