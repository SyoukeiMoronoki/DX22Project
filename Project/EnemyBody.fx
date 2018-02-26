struct appdata
{
  float4 vertex : POSITION;
  float2 uv : TEXCOORD0;
};

struct v2f
{
  float2 uv : TEXCOORD0;
  float4 vertex : SV_POSITION;
  float4 color : COLOR0;
};

texture _MainTex;
sampler _MainTexSampler = sampler_state
{
  Texture = _MainTex;
  MipFilter = LINEAR;
  MinFilter = LINEAR;
  MagFilter = LINEAR;
};

float4x4 _WorldViewProj;
float4x4 _World;
float4 _Diffuse;
float4 _Ambient;

float _LightBrightness;
float4 _LightDiffuse;
float3 _LightPosition;
float3 _LightDirection;

float3 _ViewDirection;

bool _UseEar;

float2 _UV0 = float2(0.0f, 0.0f);
float2 _UV1 = float2(1.0f, 1.0f);
float _Width = 1.0f;
float _Height = 1.0f;

static const int GRID_COUNT = 16;
static const float GRID_WIDTH = 0.002f;

v2f vert(appdata v)
{
  v2f o;
  v.vertex.x *= _Width;
  v.vertex.y *= _Height;
  o.vertex = mul(v.vertex, _WorldViewProj);
 
  v.uv *= _UV1 - _UV0;
  v.uv += _UV0; 
  o.uv = v.uv;
  
  float4 vertex = v.vertex * 0.0f;
  vertex.w = 1.0f;
  float3 vPos = mul(vertex, _World);
  float3 vL = vPos - _LightPosition;
  float3 normN = normalize(vL); 
  float3 normL = normalize(_LightDirection);
  float3 normV = normalize(_ViewDirection);
  float lengthL = length(vL);
  float dotNL = dot(normN, normL);
  float dotNV = dot(normN, normV);
  dotNL += dotNV * step(0.0f, -dotNV);
  float L = _LightBrightness * dotNL / (lengthL * lengthL * 0.25f);  // Œõ‚Ì‹­‚³
  L = max(L, 0.0f);
  o.color = _Diffuse * (_LightDiffuse * L + _Ambient * max(0.0f, 1.0f - L));
  return o;
}

float4 frag(v2f i) : SV_TARGET
{
  if (_UseEar)
  {
    i.uv.y += 0.5f;
    return tex2D(_MainTexSampler, i.uv);
  }
  return tex2D(_MainTexSampler, i.uv) * i.color;
}

technique Default
{
  pass
  {
    AlphaBlendEnable = TRUE;
    BlendOp = ADD;
    SrcBlend = SRCALPHA;
    DestBlend = INVSRCALPHA;
    ShadeMode = FLAT;
    ZEnable = TRUE;
    vertexshader = compile vs_2_0 vert();
    pixelshader = compile ps_2_0 frag();
  }
}
