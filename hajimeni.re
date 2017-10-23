#@# VRコンテンツのつくりかた2 技術書典3
#@# （）かっこは全角統一する。
#@# ユーザ入力は""ダブルクォーテーション、メニュー表示文字列は「」かぎかっこにでくくる。

= はじめに

半年前にはもうそろそろXR元年がバズっていると考えていたのですが、よく言われる通りVRのハイプ・サイクルが少しフェーズが進んだところまでいってしまって落ち着いていたり、意外とARが単独で盛り上がっており、iPhoneのほんわかとした影響力を感じる2017年をお過ごしのみなさま、いかがおすごしでしょうか。筆者のyoutenと申します。
@<br>{}

本書は、以下のような方をターゲットにしています。

 * もうそろそろ日本でもデビューしてメジャー街道まっしぐらが約束されているはずのDaydreamのことが知りたい
 * Daydream Viewを買わずになんとかDaydreamを試す方法が知りたい
 * VRやAndroidやUnityやプログラミングについてちょっとは知っていて、Daydreamアプリを開発してみたい

== 賞味期限とリポジトリ公開について

なお、本書は記載内容の賞味期限が切れてしまうことへのアップデート対応、あまり紙メディアが向いていない環境等のバージョンアップに追従するため、初版以降のPDFと関連ファイル一式を全て以下のリポジトリで公開予定です。
あらかじめご了承ください。

 * @<href>{https://github.com/youten/howto-create-vr-contents2}
 ** Re:VIEWの素材一式、出力PDF、関連プロジェクトのソースコードを全て含む想定です。

本書のうち、私youtenが著作権を有する範囲のライセンスについては、文章はCC-BY 4.0ライセンス@<fn>{cc-by-4}、ソースコードについてはApache License v2@<fn>{apache-license-v2}を適用します。

本書籍はRe:VIEWで作成されており、その設定ファイル等について、MITライセンス@<fn>{mit-license}に基づき「C89 初めてのRe:VIEW v2」リポジトリ@<fn>{techbooster-c89-review-v2}で公開されているものを利用させていただいております。

表紙他、高崎柚乃モデル@<fn>{cs-reporters-yuno}をCC-BY 4.0ライセンス@<fn>{cc-by-4}に基づき利用させていただいております。

//footnote[mit-license][@<href>{https://opensource.org/licenses/MIT}]
//footnote[techbooster-c89-review-v2][@<href>{https://github.com/TechBooster/C89-FirstStepReVIEW-v2}]
//footnote[cs-reporters-yuno][©Gugenka® from CS-REPORTERS.INC/YUNO @<href>{https://gugenka.jp/original/yuno-3d.php}]
//footnote[cc-by-4][@<href>{https://creativecommons.org/licenses/by/4.0/legalcode.ja}]
//footnote[apache-license-v2][@<href>{http://www.apache.org/licenses/LICENSE-2.0}]

