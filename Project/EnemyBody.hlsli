struct appdata
{
  float4 vertex : POSITION;
  float2 uv : TEXCOORD0;
};

struct v2f
{
  float2 uv : TEXCOORD0;
  float4 vertex : SV_POSITION;
};

float4x4 _WorldViewProj;
float4 _Diffuse;

bool _UseEye;

static const int GRID_COUNT = 16;
static const float GRID_WIDTH = 0.002f;

v2f vert(appdata v)
{
  v2f o;
  o.vertex = mul(v.vertex, _WorldViewProj);
  o.uv = v.uv;
  return o;
}

float4 frag(v2f i) : SV_TARGET
{
  if (!_UseEye)
  {
    return _Diffuse;
  }
  float d = 1.0f / GRID_COUNT;
  float dx = fmod(i.uv.x, d) - d * 0.5f;
  float dy = fmod(i.uv.y, d) - d * 0.5f;
  if (abs(dx) < GRID_WIDTH || abs(dy) < GRID_WIDTH)
  {
    return float4(1.0f, 1.0f, 1.0f, 1.0f);
  }
  float4 col = _Diffuse;
  col.a *= 0.2f;
  return col;
}

technique Default
{
  pass
  {
    vertexshader = compile vs_2_0 vert();
    pixelshader = compile ps_2_0 frag();
  }
}
