echo 

APP_DIR="/home/ubuntu/group_11/backend"
APP_NAME="app.js"
BRANCH="main"

echo "git pull..."
cd $APP_DIR
git fetch origin
git checkout $BRANCH
git pull origin $BRANCH
chmod +x /home/ubuntu/group_11/linux/deploy-backend.sh
npm install

echo "update & upgrade"
sudo apt update -y
sudo apt upgrade -y

echo "pm2 reload"
pm2 restart group11-backend

echo "nginx restart..."
sudo cp /home/ubuntu/group_11/linux/backend /etc/nginx/sites-available
sudo systemctl reload nginx

echo "deploy ready"