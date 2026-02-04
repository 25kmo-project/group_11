echo -e 

APP_DIR = "/home/ubuntu/group_11/backend"
APP_NAME = "app.js"
BRANCH = "backend-linux"

echo "update & upgrade"
sudo apt update
sudo apt upgrade 

echo "git pull..."
cd $APP_DIR
git fetch origin
git checkout $BRANCH
git pull origin $BRANCH
chmod +x /home/ubuntu/group_11/linux
npm install

echo "pm2 reload"
pm2 restart group11-backend
