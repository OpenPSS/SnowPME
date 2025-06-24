cd subprojects/LibCXML
git checkout main
git add -A 
git commit -m %%1
git push
cd ../..

cd subprojects/LibPssMono/pss-mono
git checkout mono-2-11
git add -A 
git commit -m %%1
git push
cd ../..

cd subprojects/LibMonoBridge
git checkout main
git add -A 
git commit -m %%1
git push
cd ../..

git submodule update --remote --merge
