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

float4 _Horizon;
float4 _EarthLight;

v2f vert(appdata v)
{
  v2f o;
  o.vertex = mul(v.vertex, _WorldViewProj);
  o.uv = v.uv;
  return o;
}

const float pi = 3.14159265358979f;
const float pi2 = 3.14159265358979f * 2.0f;

float4 frag(v2f i) : SV_TARGET
{
  float4 col = _Diffuse;
  float d = (0.5f - abs(i.uv.y - 0.5f)) * 2.0f;
  //col += d2 * _Horizon;
  col += pow(d, 8) * _Horizon;
  col += pow(d, 100) * _EarthLight;
  return col;
}

technique Default
{
  pass
  {
    AlphaBlendEnable = FALSE;
    ShadeMode = FLAT;
    ZEnable = TRUE;
    vertexshader = compile vs_2_0 vert();
    pixelshader = compile ps_2_0 frag();
  }
}
