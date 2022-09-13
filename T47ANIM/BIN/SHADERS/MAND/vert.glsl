#version 330

out vec2 DP;

void main( void )
{
  float s = 0.8;
  vec2 p;

  if (gl_VertexID == 0)
    p = vec2(-s, s);
  if (gl_VertexID == 1)
    p = vec2(-s, -s);
  if (gl_VertexID == 2)
    p = vec2(s, s);
  if (gl_VertexID == 3)
    p = vec2(s, -s);

  DP = p;
  gl_Position = vec4(p, 0, 1);
}

