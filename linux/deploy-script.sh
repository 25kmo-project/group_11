echo 

APP_DIR="/home/ubuntu/group_11/backend"
APP_NAME="app.js"
BRANCH="backend-linux"

echo "update & upgrade"
sudo apt update -y
sudo apt upgrade -y

echo "git pull..."
cd $APP_DIR
git fetch origin
git checkout $BRANCH
git pull origin $BRANCH
chmod +x /home/ubuntu/group_11/linux/deploy-backend.sh
npm install

echo "pm2 reload"
pm2 restart group11-backend

echo "deploy valmis"