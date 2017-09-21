echo "Retrieving Assets"
git clone https://github.com/NodziGames/Bomberman_Assets.git BA
mv -f BA/Assets .
mv -f BA/Libs .
rm -rf BA
