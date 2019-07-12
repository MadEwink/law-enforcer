//
// Created by mad on 01/06/19.
//

#include "pch.h"
#include "Boss.h"
#include "Entity.h"

Boss::Boss(b2World &world, b2Vec2 coordonnees, int pvmax, int damage_attack, int damage_dash, int damage_jump,
	int damage_contact, int attack_stun, int dash_stun, int jump_stun, int dash_speed) :
	Entity(coordonnees, pvmax, damage_attack, damage_dash, damage_jump, attack_stun, dash_stun, jump_stun, dash_speed),
	damage_contact(damage_contact),
	landing_time(45),
	landing_time_left(0)
{
    b2BodyDef bodyDef;
    b2PolygonShape groundbox;
    b2FixtureDef fixtureDef;
    coordonnees_sfml=convert_coords(this->coordonnees, -BOSS_SIZE*PIXELS_BY_METER,-BOSS_SIZE*PIXELS_BY_METER);
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = true;
    bodyDef.position.Set(this->coordonnees.x, this->coordonnees.y);
    body = world.CreateBody(&bodyDef);
    // groundbox (collisions with ground)
    groundbox.SetAsBox(BOSS_SIZE, BOSS_SIZE/10.0f, {0, -BOSS_SIZE+BOSS_SIZE/20.0f}, 0);
    fixtureDef.shape = &groundbox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.userData = (void*)entity_groundbox;
    body->CreateFixture(&fixtureDef);
    // groundDetector (decides if can jump)
    b2PolygonShape groundDetector;
    groundDetector.SetAsBox(BOSS_SIZE-(BOSS_SIZE/20.0f),BOSS_SIZE/20.0f, {0,-BOSS_SIZE}, 0);
    b2FixtureDef gDec_fixtureDef;
    gDec_fixtureDef.shape = &groundDetector;
    gDec_fixtureDef.isSensor = true;
    gDec_fixtureDef.userData = (void*)boss_footsensor;
    body->CreateFixture(&gDec_fixtureDef);
    // contact hitbox
    b2PolygonShape contact_hitbox;
    contact_hitbox.SetAsBox(BOSS_SIZE, BOSS_SIZE);
    b2FixtureDef c_h_fDef;
    c_h_fDef.shape = &contact_hitbox;
    //c_h_fDef.isSensor = true;
    c_h_fDef.userData = (void*)boss_contact_hitbox;
    body->CreateFixture(&c_h_fDef);
    b2PolygonShape hurtbox;
    hurtbox.SetAsBox(BOSS_SIZE, BOSS_SIZE);
    b2FixtureDef hb_fDef;
    hb_fDef.shape = &hurtbox;
    hb_fDef.isSensor = true;
    hb_fDef.userData = (void*)boss_hurtbox;
    body->CreateFixture(&hb_fDef);
	//jump attack hitbox
	b2CircleShape jump_attack_shape;
	jump_attack_shape.m_p.Set(0, -BOSS_SIZE);
	jump_attack_shape.m_radius = 2 * BOSS_SIZE;
	b2FixtureDef jump_attack_hitbox;
	jump_attack_hitbox.shape = &jump_attack_shape;
	jump_attack_hitbox.isSensor = true;
	jump_attack_hitbox.userData = (void*) boss_jump_hitbox;
	body->CreateFixture(&jump_attack_hitbox);

	sheet.loadFromFile("../Sprites/The_Strong.png");
}

void Boss::draw(sf::RenderWindow &window) {
    coordonnees_sfml=convert_coords(body->GetPosition(), -BOSS_SIZE*PIXELS_BY_METER,-BOSS_SIZE*PIXELS_BY_METER);
	
	if (is_fall_attacking) {
		sf::CircleShape jump_hitbox((2 * BOSS_SIZE)*PIXELS_BY_METER);
		sf::Vector2f delta1(-BOSS_SIZE*PIXELS_BY_METER , 0); // (0, 1) due to position + (-1, -1) due to sfml being in the corner and the size being 2
		jump_hitbox.setPosition(coordonnees_sfml + delta1);
		jump_hitbox.setFillColor(sf::Color(255, 0, 0, 100));
		window.draw(jump_hitbox);
	}

    //Keep to visualize hitbox on Debug
	sf::RectangleShape shape({BOSS_SIZE*PIXELS_BY_METER*2.0,BOSS_SIZE*PIXELS_BY_METER*2.0});
    shape.setPosition(coordonnees_sfml);
    shape.setFillColor(sf::Color(145,215,255));
	window.draw(shape);

	sprite.setPosition(coordonnees_sfml);
	sprite.setTexture(sheet);
    window.draw(sprite);
}

void Boss::update(const Inputs &inputs, WorldRules &worldRules) {
    if (time_without_control_left <= 0)
    {
        has_control = true;
    }
    b2Vec2 speed_applied = body->GetLinearVelocity();
    if (has_control)
        jump(worldRules.jump, true, speed_applied.y);
    else
        time_without_control_left--;
    if (time_ejection_left > 0)
    {
        time_ejection_left --;
        speed_applied = ejection_speed;
    }
    is_facing_right = (speed_applied.x > 0);
    body->SetLinearVelocity(speed_applied);
}

void Boss::do_jump(bool input_jump, float32 &current_vspeed) {
	if (!is_fall_attacking) {
		if (can_jump) current_vspeed += 4;
	}
	else { //touches the ground and attacks
		if (landing_time_left == 0) {
			is_fall_attacking = false;
		}
		else { landing_time_left--; }
	}
}

void Boss::setJump(bool jump) {
	if (!can_jump && jump) {//upon landing
		is_fall_attacking = true;
		landing_time_left = landing_time;
	}
	//if (jump && anim != player_jump) anim = player_idle;
	can_jump = jump;
	
}

void Boss::dash(bool world_dash_rule, bool input_dash, b2Vec2 &current_speed) {}

void Boss::random_move(float32 &current_hspeed) {
    if ((int)(body->GetPosition().x - body->GetPosition().y) % 30 > 15)
        current_hspeed -= 3;
    else
        current_hspeed += 3;
}

int Boss::get_damage_contact() const { return damage_contact; }