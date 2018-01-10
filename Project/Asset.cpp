#include "Asset.h"

namespace Asset
{

namespace Spine
{
SpineResource Asset::Spine::TEST("Asset/spine/skeleton");
SpineResource ANUBIS("Asset/spine/anubis");
} // namespace Spine

namespace Model
{
ModelData CART("Asset/model/cart/cart.x");
ModelData SKYBOX("Asset/model/skybox/skybox.x");
ModelData DOITYU("Asset/model/doityu/doityu.x");;
} // namespace Model

namespace Texture
{
class Texture ENEMY_WEAK_POINT("Asset/texture/enemy/weak_point.png");
class Texture ENEMY_ZAKO1("Asset/texture/enemy/zako1.png");
class Texture ENEMY_ZAKO2("Asset/texture/enemy/zako2.png");

class Texture FIELD_BG("Asset/texture/field/bg.png");
class Texture FIELD_BG_SONAR("Asset/texture/field/bg_sonar.png");
class Texture FIELD_BOYA("Asset/texture/field/boya.png");

class Texture FONT_NUMBER("Asset/texture/font/number.png");

class Texture PLAYER_BULLET("Asset/texture/player/bullet.png");
class Texture PLAYER_TURGET("Asset/texture/player/target.png");

class Texture TEXT_BONUS("Asset/texture/text/BONUS.png");
class Texture TEXT_HP("Asset/texture/text/HP.png");
class Texture TEXT_PRESSBUTTON("Asset/texture/text/PressAButton.png");
class Texture TEXT_RESULT("Asset/texture/text/RESULT.png");
class Texture TEXT_SCORE("Asset/texture/text/SCORE.png");
class Texture TEXT_SONAR("Asset/texture/text/SONAR.png");
class Texture TEXT_TIME("Asset/texture/text/TIME.png");
class Texture TEXT_TIMEUP("Asset/texture/text/TimeUP.png");
class Texture TEXT_TITLE("Asset/texture/text/TITLE.png");

class Texture UI_EARGAUGE("Asset/texture/ui/EarGauge.png");
class Texture UI_HPGAUGE("Asset/texture/ui/HPGauge.png");
class Texture UI_PLAYER_ID("Asset/texture/ui/player_id.png");
class Texture UI_TEATER("Asset/texture/ui/teater.png");

} // namespace Texture

} // namespace Asset