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

v2f vert(appdata v)
{
  v2f o;
  o.vertex = mul(v.vertex, _WorldViewProj);
  o.uv = v.uv;
  return o;
}

float4 frag(v2f i) : SV_TARGET
{
  float4 col = _Diffuse;
  //col *= cos(i.uv.x);
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
