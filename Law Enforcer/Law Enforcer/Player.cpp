//
// Created by mad on 01/06/19.
//

#include "pch.h"
#include "global_definitions.h"
#include "Player.h"
#include "Inputs.h"

#define PLAYER_SIZE 0.3

Player::Player(b2World &world, pugi::xml_node node) :
        Entity(world, node),
    jump_time_max(node.child("jump_time_max").attribute("value").as_int(0)),
    jump_time_left(node.child("jump_time_left").attribute("value").as_int(0)),
    max_speed(node.child("max_speed").attribute("value").as_int(0)),
    jump_speed(node.child("jump_speed").attribute("value").as_int(0)),
    contact_stun(node.child("contact_stun").attribute("value").as_int(0)),
    anim(player_idle),
    sprite_size(40),
    walk_time(0),
    change_walk_time(20)
{
    sheet.loadFromFile("../Sprites/Player.png");
    sprite.setTexture(sheet);
}

Player::Player(b2World &world, b2Vec2 coordonnees, int pvmax) :
	Entity(coordonnees, pvmax, 5, 5, 5, 0, 0, 0, 2 * 10),
	jump_time_max(15),
	jump_time_left(0),
	max_speed(5),
	jump_speed(8),
	contact_stun(30),
	anim(player_idle),
	sprite_size(40),
	walk_time(0),
	change_walk_time(20)
{
    b2BodyDef bodyDef;
    b2PolygonShape groundbox;
    b2FixtureDef fixtureDef;
    coordonnees_sfml=convert_coords(this->coordonnees, -PLAYER_SIZE*PIXELS_BY_METER,-PLAYER_SIZE*PIXELS_BY_METER);
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = true;
    bodyDef.position.Set(this->coordonnees.x, this->coordonnees.y);
    body = world.CreateBody(&bodyDef);
    // groundbox (collision with platforms)
    groundbox.SetAsBox(PLAYER_SIZE, PLAYER_SIZE/10.0f, {0, -PLAYER_SIZE+PLAYER_SIZE/20.0f}, 0);
    fixtureDef.shape = &groundbox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.userData = (void*)entity_groundbox;
    body->CreateFixture(&fixtureDef);
    // groundDetector (decides whether can jump)
    b2PolygonShape groundDetector;
    groundDetector.SetAsBox(PLAYER_SIZE-(PLAYER_SIZE/20.0f),PLAYER_SIZE/20.0f, {0,-PLAYER_SIZE}, 0);
    b2FixtureDef gDec_fixtureDef;
    gDec_fixtureDef.shape = &groundDetector;
    gDec_fixtureDef.isSensor = true;
    gDec_fixtureDef.userData = (void*)player_footsensor;
    body->CreateFixture(&gDec_fixtureDef);
    // hurtbox (take damage)
    b2PolygonShape hurtbox;
    hurtbox.SetAsBox(PLAYER_SIZE,PLAYER_SIZE);
    b2FixtureDef hb_fdef;
    hb_fdef.shape = &hurtbox;
    //hb_fdef.isSensor = true;
    hb_fdef.userData = (void*)player_hurtbox;
    body->CreateFixture(&hb_fdef);
    // jump_hitbox
    b2PolygonShape jump_hitbox;
    jump_hitbox.SetAsBox(PLAYER_SIZE-(PLAYER_SIZE/20.0f), PLAYER_SIZE/1.0f, {0,-PLAYER_SIZE}, 0);
    b2FixtureDef j_h_fDef;
    j_h_fDef.shape = &jump_hitbox;
    j_h_fDef.isSensor = true;
    j_h_fDef.userData = (void*)player_jump_hitbox;
    body->CreateFixture(&j_h_fDef);
    // dash hitbox
    b2CircleShape dash_hitbox_right;
    dash_hitbox_right.m_p = {PLAYER_SIZE, 0};
    dash_hitbox_right.m_radius = {PLAYER_SIZE+PLAYER_SIZE/3.0f};
    b2FixtureDef d_h_r_fDef;
    d_h_r_fDef.shape = &dash_hitbox_right;
    d_h_r_fDef.isSensor = true;
    d_h_r_fDef.userData = (void*)player_dash_hitbox;
    body->CreateFixture(&d_h_r_fDef);
    b2CircleShape dash_hitbox_left;
    dash_hitbox_left.m_p = {-PLAYER_SIZE, 0};
    dash_hitbox_left.m_radius = {PLAYER_SIZE+PLAYER_SIZE/3.0f};
    b2FixtureDef d_h_l_fDef;
    d_h_l_fDef.shape = &dash_hitbox_left;
    d_h_l_fDef.isSensor = true;
    d_h_l_fDef.userData = (void*)player_dash_hitbox;
    body->CreateFixture(&d_h_l_fDef);

	sheet.loadFromFile("../Sprites/Player.png");
	sprite.setTexture(sheet);
}

void Player::draw(sf::RenderWindow &window) {
    coordonnees_sfml=convert_coords(body->GetPosition(), -PLAYER_SIZE*PIXELS_BY_METER,-PLAYER_SIZE*PIXELS_BY_METER);
    
	if (is_fall_attacking) {
		sf::RectangleShape jump_hitbox({ 2 * (PLAYER_SIZE - (PLAYER_SIZE / 20.0f))*PIXELS_BY_METER, 2 * (PLAYER_SIZE / 1.0f)*PIXELS_BY_METER });
		sf::Vector2f delta4((PLAYER_SIZE / 20.0f)*PIXELS_BY_METER, PLAYER_SIZE*PIXELS_BY_METER);
		jump_hitbox.setPosition(coordonnees_sfml + delta4);
		jump_hitbox.setFillColor(sf::Color(255, 0, 0, 100));
		window.draw(jump_hitbox);
	}
	if (is_dashing) {
		sf::CircleShape dash_hitbox((PLAYER_SIZE + PLAYER_SIZE / 3.0f)*PIXELS_BY_METER);
		sf::Vector2f delta5(2 * (-PLAYER_SIZE / 3.0f)*PIXELS_BY_METER, (-PLAYER_SIZE / 3.0f)*PIXELS_BY_METER);
		if (is_facing_right) delta5.x += 2 * PLAYER_SIZE*PIXELS_BY_METER - dash_hitbox.getRadius();
		dash_hitbox.setPosition(coordonnees_sfml + delta5);
		dash_hitbox.setFillColor(sf::Color(255, 0, 0, 100));
		window.draw(dash_hitbox);
	}
	//to visualize hitbox
	/*
	sf::RectangleShape shape({PLAYER_SIZE*PIXELS_BY_METER*2.0,PLAYER_SIZE*PIXELS_BY_METER*2.0});
	shape.setPosition(coordonnees_sfml);
	shape.setFillColor(sf::Color(145,215,255));
	window.draw(shape);
	 */
	

	if (is_facing_right) { sprite.setScale(sf::Vector2f(1, 1)); }
	else { 
		sprite.setScale(sf::Vector2f(-1, 1));
		coordonnees_sfml.x += sprite_size*0.8f;
	}
	sprite.setPosition(coordonnees_sfml);
	sprite.setTextureRect(sf::IntRect(anim*sprite_size, 0, sprite_size, sprite_size));
	window.draw(sprite);
}

void Player::update(const Inputs &inputs, WorldRules &worldRules) {
    b2Vec2 speed_applied(body->GetLinearVelocity());
    if (time_without_control_left <= 0)
    {
        has_control = true;
    }
    if (has_control && inputs.get_pressed(left))
    {
        speed_applied.x = -max_speed;
        is_facing_right = false;
    }
    else if (has_control && inputs.get_pressed(right))
    {
        speed_applied.x = max_speed;
        is_facing_right = true;
    }
    else
    {
        if (abs(speed_applied.x) < 0.7f) speed_applied.x = 0;
        if (speed_applied.x > 0) speed_applied.x -= 0.7f;
        else if (speed_applied.x < 0) speed_applied.x += 0.7f;
    }
    if (has_control) {
        jump(worldRules.jump, inputs.get_pressed(action_key::jump), speed_applied.y);
        dash(worldRules.dash, inputs.get_pressed(action_key::dash), speed_applied);
    }
    else
    {
        time_without_control_left--;
    }
    if (time_ejection_left > 0)
    {
        time_ejection_left--;
        speed_applied = ejection_speed;
    }
	if (speed_applied.x != 0) {
		//walk animation
		if (anim <= player_walk || (anim == player_hurt && has_control == true)) { // anim = idle or walk or after being hurt
			walk_time++;
			if (walk_time > change_walk_time) {
				walk_time -= change_walk_time;
				if (anim == player_idle) { anim = player_walk; }
				else { anim = player_idle; }
			}
		}
		else { walk_time = change_walk_time; }
	}
    body->SetLinearVelocity(speed_applied);
}

void Player::do_jump(bool input_jump, float32 &current_vspeed) {
    auto contact = body->GetContactList();
    if (input_jump) {
        if (can_jump) {
            current_vspeed = jump_speed;
            jump_time_left = jump_time_max;
			anim = player_jump;
        } else if (jump_time_left > 0) {
            current_vspeed = jump_speed - (jump_time_max - jump_time_left) * (jump_speed / jump_time_max);
            jump_time_left--;
        }
    } else {
        jump_time_left = 0;
    }
	if (current_vspeed < 0 && !can_jump) {
		is_fall_attacking = true;
		anim = player_fall;
	}
}

void Player::setJump(bool jump) {
	Entity::setJump(jump);
	if (jump && anim!=player_jump) anim = player_idle;
}

void Player::dash(bool world_dash_rule, bool input_dash, b2Vec2 &current_speed) {
    if (world_dash_rule && input_dash)
    {
        is_dashing = true;
		anim = player_dash;
        has_control = false;
        time_without_control_left = 30;
        time_ejection_left = 60;
        ejection_speed = {(float32)dash_speed, 0};
        if (!is_facing_right) ejection_speed *= -1;
    } else{
        is_dashing = false;
		if (anim == player_dash) anim = player_idle;
    }
}

void Player::take_damage(int damage, int time_without_control, b2Vec2 ejection_speed) {
	Entity::take_damage(damage, time_without_control, ejection_speed);
	if (damage != 0) { anim = player_hurt; }
}

int Player::get_contact_stun() const { return contact_stun; }

